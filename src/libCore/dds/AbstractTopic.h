#pragma once

#include <cstdint>
#include <memory>
#include <libCore/dds/TopicType.h>
#include <libCore/dds/SerializationFormat.h>
#include <libCore/dds/SerializationContainer.h>


namespace core
{
	namespace dds
	{

		/**
		 * @brief Base class for all kinds of distributed topics
		 */
		class AbstractTopic
		{
			public:
				/**
				 * @brief Constructor
				 */
				AbstractTopic()=default;


				/**
				 * @brief Destructor
				 */
				virtual
				~AbstractTopic()=default;


				/**
				 * @brief Topics have types
				 * @return identifies the topic
				 */
				virtual
				TopicType
				type() const =0;


				/**
				 * @brief Getter
				 * @return name of the topic
				 */
				virtual
				const char*
				typeName() const =0;


				/**
				 * @brief Can this message be serialized in the given mode?
				 * @return yes|no
				 */
				virtual
				bool
				canSerialize(const core::dds::SerializationFormat format) const noexcept =0;


				/**
				 * @brief Serialize into container
				 * @param [in] container package where to store result
				 */
				virtual
				void
				serialize(std::shared_ptr<core::dds::SerializationContainer> pContainer) const=0;


				/**
				 * @brief Serialize from container
				 * @param [in] container package  where to read from
				 */
				virtual
				void
				deserialize(std::shared_ptr<const core::dds::SerializationContainer> pContainer) =0;


				/**
				 * @brief Topics of same type may coexist with different keys.
				 * @return key identifier
				 */
				virtual
				std::uint64_t
				key() const noexcept =0;

		};

	}
}
