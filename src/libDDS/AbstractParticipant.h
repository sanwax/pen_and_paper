#pragma once


#include <string>
#include <libDDS/ParticipantId.h>


namespace dds
{
	/**
	 * @brief A participant in a DDS network
	 */
	class AbstractParticipant
	{
		public:
			/**
			 * @brief Constructor
			 */
			AbstractParticipant() = default;


			/**
			 * @brief Destructor
			 */
			virtual
			~AbstractParticipant() = default;


			/**
			 * @brief Getter
			 * @return participant identifier
			 */
			virtual
			dds::ParticipantId
			id() const noexcept=0;


			/**
			 * @brief Getter
			 * @return participant name
			 */
			virtual
			const std::string &
			name() const noexcept=0;


		protected:
			/**
			 * @brief Creates a new pseudo-unique participant id
			 * @return participant id
			 */
			static
			dds::ParticipantId
			createParticipantId() noexcept;
	};
}
