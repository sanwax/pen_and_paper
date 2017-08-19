
#include <cassert>
#include <libDDS/Exception.h>
#include <libDDS/AbstractTopic.h>
#include <libDDS/TopicExchange.h>
#include <shared_mutex>


namespace dds
{

	TopicExchange::TopicExchange():
		dds::AbstractTopicExchange(),
	    mParticipantId(dds::AbstractParticipant::createParticipantId()),
	    mParticipantName("/dds/TopicExchange"),
	    mClock{1}
	{
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
	TopicExchange::registerParticipant(dds::AbstractParticipant *pParticipant)
	{
		//inspect pointer
		if (pParticipant==nullptr)
		{
			//ignore
			return;
		}
		//fetch participant id
		const auto id=pParticipant->id();
		assert(id!=0);
		//insert into map
		std::unique_lock<std::shared_timed_mutex> lock(mParticipantMutex);
		const auto iter=mParticipantMap.find(id);
		if (iter==mParticipantMap.end())
		{
			mParticipantMap.insert(std::make_pair(id,pParticipant));
		}
		else
		{
			if (iter->second!=pParticipant)
			{
				throw dds::Exception("Double registration attempt with differnet pointers. (key collision?)");
			}
			//ignore double registration attempt
			assert(false);
		}
	}

	void
	TopicExchange::unregisterParticipant(dds::AbstractParticipant *pParticipant)
	{
		//inspect pointer
		if (pParticipant==nullptr)
		{
			//ignore
			return;
		}
		//fetch participant id
		const auto id=pParticipant->id();
		assert(id!=0);
		//insert into map
		std::unique_lock<std::shared_timed_mutex> lock(mParticipantMutex);
		const auto iter=mParticipantMap.find(id);
		if (iter!=mParticipantMap.end())
		{
			if (iter->second==pParticipant)
			{
				mParticipantMap.erase(iter);
			}
			else
			{
				throw Exception("Invalid participant/id pair tries to unregister.");
			}
		}
	}

	void
	TopicExchange::publish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic)
	{
		//inspect pointer
		if (!pTopic)
		{
			//invalid topic
			throw Exception("Unable to publish topic: nullptr.");
		}
		//test: sender must be known
		{
			std::shared_lock<std::shared_timed_mutex> lock(mParticipantMutex);
			if (mParticipantMap.find(sender)==mParticipantMap.end())
			{
				throw Exception("Unable to publish topic. Sender unknown.");
			}
		}
		//all tests passed: inspect/prepare topic
		const auto topicType=pTopic->type();
		pTopic->dynamicProperties()->mSender=sender;
		pTopic->dynamicProperties()->mSenderClock=mClock.tick();
		pTopic->dynamicProperties()->mSenderExchange=mParticipantId;
		//finalize topic
		std::shared_ptr<const dds::AbstractTopic> pSharedTopic{std::move(pTopic)};
		//insert topic into big picture
		std::unique_lock<std::shared_timed_mutex> lock(mTopicMutex);
		mBigPicture[topicType][pSharedTopic->key()]=pSharedTopic;
		//fill event queue
		auto range=mSubscriptionMap.equal_range(topicType);
		for (auto dst=range.first;dst!=range.second;++dst)
		{
			mEventQueue.push_back(std::make_pair(dst->first,pSharedTopic));
		}
	}

	void
	TopicExchange::unpublish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic)
	{

	}

	void
	TopicExchange::unpublish(const dds::ParticipantId sender, const dds::TopicType type)
	{

	}

	void
	TopicExchange::subscribe(const dds::ParticipantId receiver, const dds::TopicType type, bool sendExisting, std::unique_ptr<AbstractTopicExchange::tFilterFunction> pFilter)
	{

	}

	void
	TopicExchange::unsubscribe(const dds::ParticipantId receiver, const dds::TopicType type)
	{

	}

	void
	TopicExchange::unsubscribe(const dds::ParticipantId receiver)
	{

	}


}
