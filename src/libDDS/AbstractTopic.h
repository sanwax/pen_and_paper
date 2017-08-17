#pragma once

#include <cstdint>
#include <memory>
#include <libDDS/TopicType.h>
#include <libDDS/SerializationFormat.h>
#include <libDDS/SerializationContainer.h>

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
			AbstractTopic() = default;
			
			/**
			 * @brief Destructor
			 */
			virtual ~AbstractTopic() = default;
			
			/**
			 * @brief Topics have types
			 * @return identifies the topic
			 */
			virtual TopicType
			type() const =0;

			/**
			 * @brief Getter
			 * @return name of the topic
			 * @note Format should be namespace/nestednamespace/classname
			 * @note E.g. dds/topics/MyTopic
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
			canSerialize(const dds::SerializationFormat format) const noexcept =0;

			/**
			 * @brief Serialize into container
			 * @param [in] container package where to store result
			 */
			virtual
			void
			serialize(std::shared_ptr<dds::SerializationContainer> pContainer) const=0;

			/**
			 * @brief Serialize from container
			 * @param [in] container package  where to read from
			 */
			virtual
			void
			deserialize(std::shared_ptr<const dds::SerializationContainer> pContainer) =0;

			/**
			 * @brief Topics of same type may coexist with different keys.
			 * @return key identifier
			 */
			virtual std::uint64_t
			key() const noexcept =0;
			
	};

}
