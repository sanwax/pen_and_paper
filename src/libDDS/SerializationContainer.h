#pragma once

#include <libDDS/SerializationFormat.h>

namespace dds
{
	
	/**
	 * @brief Container for serialization activities
	 */
	class SerializationContainer
	{
		public:
			/**
			 * @brief Constructor
			 */
			SerializationContainer() = default;
			
			/**
			 * @brief Destructor
			 */
			virtual ~SerializationContainer() = default;
			
			/**
			 * @brief Getter
			 * @return serialization format
			 */
			virtual dds::SerializationFormat
			format() const noexcept =0;
	};

}
