#pragma once

#include <memory>
#include <string>
#include <libDDS/ParticipantId.h>
#include <libDDS/Operation.h>


namespace dds
{
	class AbstractTopic;


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


			/**
			 * @brief Topic exchange pushes a new topic activity
			 * @param pTopic the topic
			 * @param operation the activity
			 */
			virtual
			void
			handleTopicActivity(const std::shared_ptr<const dds::AbstractTopic>& pTopic,const dds::Operation operation) noexcept =0;

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
