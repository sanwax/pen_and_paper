#pragma once


#include <memory>
#include <functional>
#include <libDDS/AbstractParticipant.h>
#include <libDDS/TopicType.h>


namespace dds
{
	class AbstractTopic;
	class AbstractParticipant;


	/**
	 * @brief Interface for topic exchange participants
	 */
	class AbstractTopicExchange:public dds::AbstractParticipant
	{
		public:
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
			 * @param pSender topic origin
			 * @param pTopic topic instance
			 */
			virtual
			void
			publish(const dds::ParticipantId sender,std::unique_ptr<dds::AbstractTopic> pTopic) = 0;


			/**
			 * @brief Remove topic by type+key
			 * @param pSender sender
			 * @param pTopic topic (with key) to delete
			 */
			virtual
			void
			unpublish(const dds::ParticipantId sender,std::unique_ptr<dds::AbstractTopic> pTopic)  = 0;


			/**
			 * @brief Remove topic by type
			 * @param pSender sender of topic
			 * @param type identifies the topic
			 */
			virtual
			void
			unpublish(const dds::ParticipantId sender,const dds::TopicType type)  = 0;


			/**
			 * @brief Subscribe a topic
			 * @param pReceiver receiver participant
			 * @param type topic type
			 * @param replayExisting replay existing topics for late joiners or just new ones?
			 */
			virtual
			void
			subscribe(const dds::ParticipantId receiver,const dds::TopicType type,bool replayExisting) =0;


			/**
			 * @brief Unsubscribe a topic
			 * @param pReceiver receiver participant
			 * @param type topic type
			 */
			virtual
			void
			unsubscribe(const dds::ParticipantId receiver,const dds::TopicType type) =0;

			/**
			 * @brief Unsubscribe a topic
			 * @param pReceiver receiver participant
			 */
			virtual
			void
			unsubscribe(const dds::ParticipantId receiver) =0;

	};

}
