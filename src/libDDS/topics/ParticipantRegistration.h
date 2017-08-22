#pragma once


#include <libDDS/AbstractTopic.h>
#include <libDDS/AbstractParticipant.h>


namespace dds
{
	class AbstractParticipant;


	namespace topics
	{
		/**
		 * @brief Topic where DDS participants are identified
		 */
		class ParticipantRegistration : public dds::AbstractTopic
		{
			public:
				/**
				 * @brief Constructor
				 */
				ParticipantRegistration() = default;


				/**
				 * @brief Destructor
				 */
				virtual
				~ParticipantRegistration() = default;


				/**
				 * @brief Topics have types
				 * @return identifies the topic
				 */
				virtual TopicType
				type() const;

				/**
				 * @brief Getter
				 * @return name of the topic
				 */
				virtual const char *
				typeName() const;

				/**
				 * @brief Can this message be serialized in the given mode?
				 * @return yes|no
				 */
				virtual bool
				canSerialize(const dds::SerializationFormat format) const noexcept;

				/**
				 * @brief Serialize into container
				 * @param [in] container package where to store result
				 */
				virtual void
				serialize(std::shared_ptr<dds::SerializationContainer> pContainer) const;

				/**
				 * @brief Serialize from container
				 * @param [in] container package  where to read from
				 */
				virtual void
				deserialize(std::shared_ptr<const dds::SerializationContainer> pContainer);


				/**
				 * @brief Update payload from AbstractParticipant class
				 * @param pParticipant instance where to read payload from
				 */
				void
				set(dds::AbstractParticipant *pParticipant);


				//paydata
				dds::ParticipantId mParticipantId=0;             ///< participant by id
				std::string mParticipantName;                    ///< participant by name
				dds::AbstractParticipant* mpParticipant=nullptr; ///< stripped by TopicExchange instance which will serve the participant
		};
	}
}