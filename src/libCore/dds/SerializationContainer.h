#pragma once


#include <libCore/dds/SerializationFormat.h>


namespace core
{
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
				SerializationContainer()=default;


				/**
				 * @brief Destructor
				 */
				virtual
				~SerializationContainer()=default;


				/**
				 * @brief Getter
				 * @return serialization format
				 */
				virtual
				core::dds::SerializationFormat
				format() const noexcept =0;
		};


	}
}

