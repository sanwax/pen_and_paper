#pragma once


#include <memory>
#include <functional>
#include <libDDS/AbstractParticipant.h>
#include <libDDS/TopicType.h>


namespace dds
{
	class AbstractTopic;


	/**
	 * @brief Interface for topic exchange participants
	 */
	class AbstractTopicExchange:public dds::AbstractParticipant
	{
		public:
			typedef std::function<bool(const std::shared_ptr<dds::AbstractTopic>&,bool)> tFilterFunction;


			/**
			 * @brief Constructor
			 */
			AbstractTopicExchange() = default;


			/**
			 * @brief Destructor
			 */
			virtual
			~AbstractTopicExchange() = default;


			/**
			 * @brief Publish a topic
			 * @param sender topic origin
			 * @param pTopic topic instance
			 */
			virtual
			void
			publish(const dds::ParticipantId& sender,std::unique_ptr<dds::AbstractTopic> pTopic) = 0;


			/**
			 * @brief Remove topic by type+key
			 * @param sender sender
			 * @param pTopic topic (with key) to delete
			 */
			virtual
			void
			unpublish(const dds::ParticipantId& sender,std::unique_ptr<dds::AbstractTopic> pTopic)  = 0;


			/**
			 * @brief Remove topic by type
			 * @param sender sender of topic
			 * @param type identifies the topic
			 */
			virtual
			void
			unpublish(const dds::ParticipantId& sender,const dds::TopicType type)  = 0;


			/**
			 * @brief Subscribe a topic
			 * @param receiver receiver participant
			 * @param type topic type
			 * @param sendExisting send existing topics or just new ones?
			 * @param pFilter a filter function
			 */
			virtual
			void
			subscribe(const dds::ParticipantId& receiver,const dds::TopicType type,bool sendExisting,std::unique_ptr<tFilterFunction> pFilter) =0;


			/**
			 * @brief Unsubscribe a topic
			 * @param receiver receiver participant
			 * @param type topic type
			 */
			virtual
			void
			unsubscribe(const dds::ParticipantId& receiver,const dds::TopicType type) =0;

	};

}
