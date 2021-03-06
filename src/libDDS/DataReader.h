#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <libDDS/TopicType.h>
#include <libDDS/Operation.h>

namespace dds
{
	
	class AbstractTopic;
	class AbstractTopicExchange;
	
	class DataReader
	{
		public:
			typedef std::function<void(const dds::TopicType, const std::shared_ptr<const dds::AbstractTopic>&, const dds::Operation op)> Callback;

			/**
			 * @brief Constructor
			 * @param [in] pExchange controller to work with
			 */
			DataReader(std::shared_ptr<dds::AbstractTopicExchange> pExchange);

			/**
			 * @brief Destructor
			 */
			virtual
			~DataReader();

			/**
			 * @brief This function receives events from the topic exchange
			 * @param [in] type of topic to handle
			 * @param [in] pTopic topic to distribute
			 * @param [in] operation kind
			 */
			virtual
			void
			handleEvent(const dds::TopicType type, std::shared_ptr<const dds::AbstractTopic> pTopic, const dds::Operation operation);

			/**
			 * @brief Subscribe a topic type, get called on any event
			 * @param [in] type of topic to subscribe
			 * @param [in] callback function to call on events
			 */
			virtual
			void
			subscribe(const dds::TopicType type, Callback callback);

			/**
			 * @brief Unsubscribe a specific topic
			 * @param [in] type of topic to unsubscribe
			 */
			virtual
			void
			unsubscribe(const dds::TopicType type);

			/**
			 * @brief Unsubscribe from all topics
			 */
			virtual
			void
			unsubscribe();

		protected:
			std::shared_ptr<dds::AbstractTopicExchange> mpExchange;                  ///< the topic exchange
			std::unordered_multimap<dds::TopicType, Callback> mCallbackMap;   ///< mapped callbacks
	};

}

