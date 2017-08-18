#pragma once

#include <memory>
#include <unordered_set>
#include <libDDS/TopicType.h>

namespace dds
{
	
	class AbstractTopic;
	class AbstractTopicExchange;
	
	/**
	 * @brief Interface to the data distribution system for publishers
	 */
	class DataWriter
	{
		public:
			/**
			 * @brief Constructor
			 * @param [in] pSwitch a dds switch entity
			 */
			explicit
			DataWriter(std::shared_ptr<dds::AbstractTopicExchange> pSwitch);

			/**
			 * @brief Destructor
			 */
			virtual
			~DataWriter();

			/**
			 * @brief Declare a new topic type
			 * @param [in] iType identifies the topic type
			 */
			void
			addTopic(const dds::TopicType iType);

			/**
			 * @brief Add a new topic type by publishing a first topic instance
			 * @param [in] pTopic first topic instance to publish
			 */
			void
			addTopic(std::unique_ptr<dds::AbstractTopic>& pTopic);

			/**
			 * @brief Publishes a new topic instance
			 * @param [in] pTopic topic instance to publish
			 */
			void
			publish(std::unique_ptr<dds::AbstractTopic>& pTopic);

			/**
			 * @brief Delete a topic type but publish one last update before
			 * @param [in] pTopic last topic instance of that type
			 */
			void
			deleteTopic(std::unique_ptr<dds::AbstractTopic>& pTopic);

			/**
			 * @brief Delete a topic type
			 * @param [in] iType identifies the topic type
			 */
			void
			deleteTopic(const dds::TopicType iType);

		protected:
			std::shared_ptr<dds::AbstractTopicExchange> mpExchange;   ///< switch to communicate with
			std::unordered_set<dds::TopicType> mTopicSet;     ///< set of registered topics
	};

}

