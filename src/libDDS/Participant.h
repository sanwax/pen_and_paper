#pragma once


#include <memory>
#include <libDDS/TopicType.h>
#include <libDDS/AbstractParticipant.h>


namespace dds
{
	class AbstractTopicExchange;


	class Participant : public dds::AbstractParticipant
	{
		public:
			/**
			 * @brief Constructor
			 * @param pExchange pointer to associated topic exchange
			 * @param sName labels the participant with a human readable name
			 */
			Participant(std::shared_ptr<dds::AbstractTopicExchange> pExchange, const std::string &sName);


			/**
			 * @brief Destructor
			 */
			virtual
			~Participant();


			/**
			 * @brief Getter
			 * @return participant identifier
			 */
			dds::ParticipantId
			id() const noexcept
			{
				return mId;
			}


			/**
			 * @brief Getter
			 * @return participant name
			 */
			virtual const std::string &
			name() const noexcept
			{
				return msName;
			}


			/**
			 * @brief Topic exchange pushes a new topic activity
			 * @param pTopic the topic
			 * @param operation the activity
			 */
			virtual void
			handleTopicActivity(const std::shared_ptr<const dds::AbstractTopic> &pTopic, const dds::Operation operation) noexcept;


			/**
			 * @brief Subscribe
			 * @param type topic type
			 * @param replayExisting replay existing topic instances
			 */
			virtual void
			subscribe(const dds::TopicType type, bool replayExisting);


			/**
			 * @brief Unsubscribe a topic by type
			 * @param type topic type
			 */
			virtual void
			unsubscribe(const dds::TopicType type);


			/**
			 * @brief Unsubscribe from all topics
			 */
			virtual void
			unsubscribe();


		protected:
			const dds::ParticipantId mId;                    ///< participant identification
			const std::string msName;                        ///< name of the participant
			std::shared_ptr<dds::AbstractTopicExchange> mpExchange;  ///< every participant needs an exchange
	};
}