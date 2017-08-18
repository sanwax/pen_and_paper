#pragma once

#include <string>
#include <memory>
#include <libDDS/ParticipantId.h>


namespace dds
{
	class TopicExchange;


	/**
	 * @brief A participant in a DDS network
	 */
	class AbstractParticipant
	{
		public:
			/**
			 * @brief Constructor
			 * @param pExchange pointer to associated topic exchange
			 * @param sName labels the participant with a human readable name
			 */
			AbstractParticipant(std::shared_ptr<dds::TopicExchange>& pExchange,const std::string& sName);


			/**
			 * @brief Destructor
			 */
			virtual
			~AbstractParticipant();


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
			virtual
			const std::string&
			name() const noexcept
			{
				return msName;
			}


		protected:
			/**
			 * @brief Creates a new pseudo-unique participant id
			 * @return participant id
			 */
			static
			dds::ParticipantId
			createParticipantId() noexcept;


			const dds::ParticipantId mId;                    ///< participant identification
			const std::string msName;                        ///< name of the participant
			std::shared_ptr<dds::TopicExchange> mpExchange;  ///< every participant needs an exchange
	};
}
