#pragma once

#include <libDDS/AbstractTopic.h>

namespace dds
{
	
	namespace topics
	{
	
		class TopicSubscription:public dds::AbstractTopic
		{
			public:
				/**
				 * @brief Constructor
				 */
				TopicSubscription()=default;

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
				virtual
				const char*
				typeName() const;

				/**
				 * @brief Can this message be serialized in the given mode?
				 * @return yes|no
				 */
				virtual
				bool
				canSerialize(const dds::SerializationFormat format) const noexcept;

				/**
				 * @brief Serialize into container
				 * @param [in] container package where to store result
				 */
				virtual
				void
				serialize(std::shared_ptr<dds::SerializationContainer> pContainer) const;

				/**
				 * @brief Serialize from container
				 * @param [in] container package  where to read from
				 */
				virtual
				void
				deserialize(std::shared_ptr<const dds::SerializationContainer> pContainer);

				/**
				 * @brief Topics of same type may coexist with different keys.
				 * @return key identifier
				 */
				virtual std::uint64_t
				key() const noexcept;


		};

	}

}
