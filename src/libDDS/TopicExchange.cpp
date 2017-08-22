#include <cassert>
#include <libDDS/Exception.h>
#include <libDDS/AbstractTopic.h>
#include <libDDS/TopicExchange.h>
#include <libDDS/topics/ParticipantRegistration.h>
#include <libDDS/stl/convenience.h>


namespace dds
{

	TopicExchange::TopicExchange() :
		dds::AbstractTopicExchange(),
		mParticipantId(dds::AbstractParticipant::createParticipantId()),
		mParticipantName("/dds/TopicExchange"),
		mClock{1},
	    mQueueThread(std::bind(&TopicExchange::processQueue,this))
	{
	}


	/*virtual*/
	TopicExchange::~TopicExchange()
	{
		//stop queue thread
		mbShutdownRequested=true;
		mQueueChangeEvent.notify_all();
		mQueueThread.join();
	}


	dds::ParticipantId
	TopicExchange::id() const noexcept
	{
		return mParticipantId;
	}


	const std::string &
	TopicExchange::name() const noexcept
	{
		return mParticipantName;
	}

	void
	TopicExchange::registerParticipant(const std::shared_ptr<const dds::topics::ParticipantRegistration> pRegistration)
	{
		//inspect pointer
		if (pRegistration == nullptr)
		{
			//ignore
			return;
		}
		if (pRegistration->mpParticipant==nullptr)
		{
			//ignore, too
			return;
		}
		//fetch participant id
		const auto id = pRegistration->mParticipantId;
		assert(id != 0);
		assert(id==pRegistration->mpParticipant->id());
		//insert into map
		std::unique_lock<std::mutex> lock(mMutex);
		const auto iter = mParticipantMap.find(id);
		if (iter == mParticipantMap.end())
		{
			mParticipantMap.insert(std::make_pair(id, pRegistration->mpParticipant));
		}
		else
		{
			if (iter->second != pRegistration->mpParticipant)
			{
				throw dds::Exception("Double registration attempt with differnet pointers. (key collision?)");
			}
			//ignore double registration attempt
			assert(false);
		}
	}

	void
	TopicExchange::unregisterParticipant(const std::shared_ptr<const dds::topics::ParticipantRegistration> pRegistration)
	{
		//inspect pointer
		if (!pRegistration)
		{
			//ignore
			return;
		}
		//fetch participant id
		const auto id = pRegistration->mParticipantId;
		assert(id != 0);
		//insert into map
		std::unique_lock<std::mutex> lock(mMutex);
		const auto iter = mParticipantMap.find(id);
		if (iter != mParticipantMap.end())
		{
			if (iter->second == pRegistration->mpParticipant)
			{
				mParticipantMap.erase(iter);
			}
			else
			{
				throw Exception("Invalid participant/id pair tries to unregister.");
			}
		}
	}


	std::shared_ptr<const dds::AbstractTopic>
	TopicExchange::finalizeTopic(const dds::ParticipantId& sender,std::unique_ptr<dds::AbstractTopic>& pTopic)
	{
		//inspect pointer
		if (!pTopic)
		{
			//invalid topic
			throw Exception("Unable to finalize topic: nullptr.");
		}
		if (!pTopic->dynamicProperties())
		{
			throw Exception("Unable to finalize topic: missing dynamic properties package.");
		}
		pTopic->dynamicProperties()->mSender = sender;
		pTopic->dynamicProperties()->mSenderClock = mClock.tick();
		pTopic->dynamicProperties()->mSenderExchange = mParticipantId;
		//finalize topic
		std::shared_ptr<const dds::AbstractTopic> pSharedTopic{std::move(pTopic)};
		return pSharedTopic;
	}


	void
	TopicExchange::publish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic)
	{
		static const dds::TopicType typeIdParticipantRegistrationTopic = AbstractTopic::resolveTypeId<topics::ParticipantRegistration>();
		//inspect pointer
		if (!pTopic)
		{
			//invalid topic
			throw Exception("Unable to publish topic: nullptr.");
		}
		//finalize topic
		const auto pSharedTopic=finalizeTopic(sender,pTopic);
		const auto topicType = pSharedTopic->type();
		//inspect topic type for dds control topics
		if (topicType == typeIdParticipantRegistrationTopic)
		{
			registerParticipant(std::dynamic_pointer_cast<const dds::topics::ParticipantRegistration>(pSharedTopic));
		}
		//enter critical section
		std::unique_lock<std::mutex> lock(mMutex);
		//test: sender must be served by us
		if (mParticipantMap.find(sender) == mParticipantMap.end())
		{
			throw Exception("Unable to publish topic. Sender unknown.");
		}
		//test if topic is already known
		const bool bIsNewTopic=mBigPicture.find(topicType)==mBigPicture.end();
		mBigPicture[topicType][pSharedTopic->key()] = pSharedTopic;
		//fill event queue
		auto range = mSubscriptionMap.equal_range(topicType);
		for (auto dst = range.first; dst != range.second; ++dst)
		{
			if (bIsNewTopic)
			{
				mEventQueue.push_back(std::make_tuple(dst->first, pSharedTopic, dds::Operation::INSERT));
			}
			else
			{
				mEventQueue.push_back(std::make_tuple(dst->first, pSharedTopic, dds::Operation::UPDATE));
			}
		}
		mQueueChangeEvent.notify_all();
	}

	void
	TopicExchange::unpublish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic)
	{
		static const dds::TopicType typeIdParticipantRegistrationTopic = AbstractTopic::resolveTypeId<topics::ParticipantRegistration>();
		//inspect pointer
		if (!pTopic)
		{
			//invalid topic
			throw Exception("Unable to unpublish topic: nullptr.");
		}
		//finalize topic
		const auto pSharedTopic=finalizeTopic(sender,pTopic);
		const auto topicType = pSharedTopic->type();
		//enter critical section
		std::unique_lock<std::mutex> lock(mMutex);
		//test: if sender is served by this topic exchange
		if (mParticipantMap.find(sender) == mParticipantMap.end())
		{
			throw Exception("Unable to unpublish topic. Sender unknown.");
		}
		//inspect topic type for dds control topics
		if (topicType == typeIdParticipantRegistrationTopic)
		{
			lock.unlock();
			unregisterParticipant(std::dynamic_pointer_cast<const dds::topics::ParticipantRegistration>(pSharedTopic));
			lock.lock();
		}
		//remove from big picture;
		auto typeIter=mBigPicture.find(topicType);
		if (typeIter==mBigPicture.end())
		{
			//never received before
			return;
		}
		auto keyIter=typeIter->second.find(pSharedTopic->key());
		if (keyIter==typeIter->second.end())
		{
			//no such key
			return;
		}
		//remove key
		typeIter->second.erase(keyIter);
		const bool bLastKeyDeleted=typeIter->second.empty();
		//remove entire type
		if (bLastKeyDeleted)
		{
			mBigPicture.erase(typeIter);
		}
		//fill event queue
		auto range = mSubscriptionMap.equal_range(topicType);
		for (auto dst = range.first; dst != range.second; ++dst)
		{
			mEventQueue.push_back(std::make_tuple(dst->first, pSharedTopic, dds::Operation::DELETE));
		}
		mQueueChangeEvent.notify_all();
	}

	void
	TopicExchange::unpublish(const dds::ParticipantId sender, const dds::TopicType type)
	{
		//enter critical section
		std::unique_lock<std::mutex> lock(mMutex);
		//test: if sender is served by this topic exchange
		if (mParticipantMap.find(sender) == mParticipantMap.end())
		{
			throw Exception("Unable to unpublish topic. Sender unknown.");
		}
		//remove from big picture;
		auto typeIter=mBigPicture.find(type);
		if (typeIter==mBigPicture.end())
		{
			//never received before
			return;
		}
		//find subscriber range
		const auto subscriberRange = mSubscriptionMap.equal_range(type);
		//walk entire map (by type) to find all topics published by sender
		auto topicIter=typeIter->second.begin();
		while (topicIter!=typeIter->second.end())
		{
			if (topicIter->second->constDynamicProperties()->mSender==sender)
			{
				//create delete events
				for (auto dst = subscriberRange.first; dst != subscriberRange.second; ++dst)
				{
					mEventQueue.push_back(std::make_tuple(dst->first, topicIter->second, dds::Operation::DELETE));
				}
				//remove topic from big picture
				topicIter=typeIter->second.erase(topicIter);
			}
			else
			{
				++topicIter;
			}
		}
		mQueueChangeEvent.notify_all();
		//test if last topic removed of that type
		if (typeIter->second.empty())
		{
			mBigPicture.erase(typeIter);
		}
	}


	void
	TopicExchange::subscribe(const dds::ParticipantId receiver, const dds::TopicType type, bool replayExisting)
	{
		//enter critical section
		std::unique_lock<std::mutex> lock(mMutex);
		//test: if receiver is served by this topic exchange
		if (mParticipantMap.find(receiver) == mParticipantMap.end())
		{
			throw Exception("Unable to subscribe topic. Unregistered receiver.");
		}
		//subscription map
		mSubscriptionMap.insert(std::make_pair(receiver,type));
		//replay existing (if required)
		if (replayExisting)
		{
			//check if topics of wanted type are available
			const auto typeIter=mBigPicture.find(type);
			if (typeIter!=mBigPicture.end())
			{
				for (auto keyIter=typeIter->second.begin();keyIter!=typeIter->second.end();++keyIter)
				{
					mEventQueue.push_back(std::make_tuple(receiver,keyIter->second, dds::Operation::REPLAY));
				}
				mQueueChangeEvent.notify_all();
			}
		}
	}

	void
	TopicExchange::unsubscribe(const dds::ParticipantId receiver, const dds::TopicType type)
	{
		//enter critical section
		std::unique_lock<std::mutex> lock(mMutex);
		//test: if receiver is served by this topic exchange
		if (mParticipantMap.find(receiver) == mParticipantMap.end())
		{
			throw Exception("Unable to unsubscribe topic. Unregistered receiver.");
		}
		//remove queue'd events
		auto queueIter=mEventQueue.begin();
		while (queueIter!=mEventQueue.end())
		{
			if (std::get<0>(*queueIter)==receiver && std::get<1>(*queueIter).get()!=nullptr && std::get<1>(*queueIter)->type()==type)
			{
				queueIter=mEventQueue.erase(queueIter);
			}
			else
			{
				++queueIter;
			}
		}
		mQueueChangeEvent.notify_all();
		//remove subscription
		const auto iter=stl::findPair(mSubscriptionMap,receiver,type);
		if (iter!=mSubscriptionMap.end())
		{
			mSubscriptionMap.erase(iter);
		}
	}

	void
	TopicExchange::unsubscribe(const dds::ParticipantId receiver)
	{
		//enter critical section
		std::unique_lock<std::mutex> lock(mMutex);
		//test: if receiver is served by this topic exchange
		if (mParticipantMap.find(receiver) == mParticipantMap.end())
		{
			throw Exception("Unable to unsubscribe topic. Unregistered receiver.");
		}
		//remove queue'd events
		auto queueIter=mEventQueue.begin();
		while (queueIter!=mEventQueue.end())
		{
			if (std::get<0>(*queueIter)==receiver)
			{
				queueIter=mEventQueue.erase(queueIter);
			}
			else
			{
				++queueIter;
			}
		}
		mQueueChangeEvent.notify_all();
		//remove subscription
		mSubscriptionMap.erase(receiver);
	}


	void
	TopicExchange::processQueue()
	{
		std::unique_lock<std::mutex> guard(mMutex);
		while (!mbShutdownRequested)
		{
			//fetch next element from the queue
			if (mEventQueue.empty())
			{
				mQueueChangeEvent.wait(guard);
				if (mbShutdownRequested)
				{
					return;
				}
			}
			if (mEventQueue.empty()==false)
			{
				const auto event = mEventQueue.front();
				mEventQueue.pop_front();
				//resolve the receiving participant
				const auto participantIter = mParticipantMap.find(std::get<0>(event));
				if (participantIter != mParticipantMap.end())
				{
					guard.unlock();
					participantIter->second->handleTopicActivity(std::get<1>(event), std::get<2>(event));
					guard.lock();
				}
			}
		}
	}


}
