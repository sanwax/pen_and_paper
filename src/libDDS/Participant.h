#pragma once

#include <memory>
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
			Participant(std::shared_ptr<dds::AbstractTopicExchange> &pExchange, const std::string &sName);


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


		protected:
			const dds::ParticipantId mId;                    ///< participant identification
			const std::string msName;                        ///< name of the participant
			std::shared_ptr<dds::AbstractTopicExchange> mpExchange;  ///< every participant needs an exchange
	};
}