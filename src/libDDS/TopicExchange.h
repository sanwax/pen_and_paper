#pragma once


#include <queue>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <memory>
#include <tuple>
#include <libDDS/AbstractTopicExchange.h>
#include <libDDS/MonotonicClock.h>
#include <libDDS/Operation.h>


namespace dds
{
	namespace topics
	{
		class ParticipantRegistration;
	}


	class TopicExchange : public dds::AbstractTopicExchange
	{
		public:
			/**
			 * @brief Constructor
			 */
			TopicExchange();


			/**
			 * @brief Destructor
			 */
			virtual
			~TopicExchange();

			ParticipantId
			id() const noexcept;

			const std::string &
			name() const noexcept;

			virtual void
			publish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic);

			virtual void
			unpublish(const dds::ParticipantId sender, std::unique_ptr<dds::AbstractTopic> pTopic);

			virtual void
			unpublish(const dds::ParticipantId sender, const dds::TopicType type);

			virtual void
			subscribe(const dds::ParticipantId receiver, const dds::TopicType type, bool replayExisting);

			virtual void
			unsubscribe(const dds::ParticipantId receiver, const dds::TopicType type);

			virtual void
			unsubscribe(const dds::ParticipantId receiver);

		protected:
			virtual void
			registerParticipant(const std::shared_ptr<const dds::topics::ParticipantRegistration> pRegistration);

			virtual void
			unregisterParticipant(const std::shared_ptr<const dds::topics::ParticipantRegistration> pRegistration);


			bool
			participantServed(const dds::ParticipantId id);


			std::shared_ptr<const dds::AbstractTopic>
			finalizeTopic(const dds::ParticipantId &sender, std::unique_ptr<dds::AbstractTopic> &pTopic);


			void
			processQueue();

			//participant part
			const dds::ParticipantId mParticipantId;
			const std::string mParticipantName;
			//Topic Exchange parts
			dds::MonotonicClock mClock;                                                         ///< a clock
			std::shared_timed_mutex mParticipantMutex;                                          ///< protects the participant map
			std::unordered_map<dds::ParticipantId, dds::AbstractParticipant *> mParticipantMap;
			std::shared_timed_mutex mTopicMutex;                                                ///< protects the big picture and subscription maps
			std::unordered_map<dds::TopicType, std::unordered_map<std::string, std::shared_ptr<const dds::AbstractTopic>>> mBigPicture;
			std::unordered_multimap<dds::TopicType, dds::ParticipantId> mSubscriptionMap;
			std::deque<std::tuple<dds::ParticipantId, std::shared_ptr<const dds::AbstractTopic>, dds::Operation>> mEventQueue;
			std::condition_variable mQueueChangeEvent;                                          ///< signals changes of the queue
			std::thread mQueueThread;                                                           ///< a thread that empties the queue
			bool mbShutdownSignaled{false};                                                     ///< flag: signal the thread to shutdown

	};
}