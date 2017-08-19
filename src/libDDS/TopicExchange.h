#pragma once

#include <queue>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <memory>
#include <libDDS/AbstractTopicExchange.h>
#include <libDDS/MonotonicClock.h>



namespace dds
{
	class TopicExchange : public dds::AbstractTopicExchange
	{
		public:
			/**
			 * @brief Constructor
			 */
			TopicExchange();


			ParticipantId
			id() const noexcept;

			const std::string &
			name() const noexcept;

			virtual void
			registerParticipant(dds::AbstractParticipant *pParticipant);

			virtual void
			unregisterParticipant(dds::AbstractParticipant *pParticipant);

			virtual void
			publish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic);

			virtual void
			unpublish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic);

			virtual void
			unpublish(const dds::ParticipantId sender, const dds::TopicType type);

			virtual void
			subscribe(const dds::ParticipantId receiver, const dds::TopicType type, bool sendExisting, std::unique_ptr<tFilterFunction> pFilter);

			virtual void
			unsubscribe(const dds::ParticipantId receiver, const dds::TopicType type);

			virtual void
			unsubscribe(const dds::ParticipantId receiver);

		protected:
			//participant part
			const dds::ParticipantId mParticipantId;
			const std::string mParticipantName;
			//Topic Exchange parts
			dds::MonotonicClock mClock;  ///< a clock
			std::shared_timed_mutex mParticipantMutex; ///< protects the participant map
			std::unordered_map<dds::ParticipantId,dds::AbstractParticipant*> mParticipantMap;
			std::shared_timed_mutex mTopicMutex; ///< protects the big picture and subscription maps
			std::unordered_map<dds::TopicType,std::unordered_map<std::string,std::shared_ptr<const dds::AbstractTopic>>> mBigPicture;
			std::unordered_multimap<dds::TopicType,dds::ParticipantId> mSubscriptionMap;
			std::deque<std::pair<dds::ParticipantId,std::shared_ptr<const dds::AbstractTopic>>> mEventQueue;

	};
}