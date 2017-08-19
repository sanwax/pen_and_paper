#pragma once


#include <cstdint>
#include <memory>
#include <string>
#include <libDDS/ParticipantId.h>
#include <libDDS/TopicType.h>
#include <libDDS/SerializationFormat.h>
#include <libDDS/SerializationContainer.h>
#include <libDDS/MonotonicClock.h>


namespace dds
{

	/**
	 * @brief Base class for all kinds of distributed topics
	 */
	class AbstractTopic
	{
		public:

			class DynamicProperties
			{
				public:
					dds::ParticipantId mSender{0};          ///< who published this topic?
					dds::MonotonicClock mSenderClock{0};    ///< when was the topic published (used to order published topics)
					dds::ParticipantId mSenderExchange{0};  ///< which exchange distributed the topic?
			};



			/**
			 * @brief Constructor
			 */
			AbstractTopic() = default;

			/**
			 * @brief Destructor
			 */
			virtual
			~AbstractTopic() = default;

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
			virtual const char *
			typeName() const =0;

			/**
			 * @brief Can this message be serialized in the given mode?
			 * @return yes|no
			 */
			virtual bool
			canSerialize(const dds::SerializationFormat format) const noexcept =0;

			/**
			 * @brief Serialize into container
			 * @param [in] container package where to store result
			 */
			virtual void
			serialize(std::shared_ptr<dds::SerializationContainer> pContainer) const =0;

			/**
			 * @brief Serialize from container
			 * @param [in] container package  where to read from
			 */
			virtual void
			deserialize(std::shared_ptr<const dds::SerializationContainer> pContainer) =0;

			/**
			 * @brief Topics of same type may coexist with different keys.
			 * @return key identifier
			 */
			virtual const std::string&
			key() const noexcept
			{
				return msKey;
			}


			/**
			 * @brief Grants read-write access to topic dynamic properties
			 * @return dynamic properties package
			 */
			virtual
			dds::AbstractTopic::DynamicProperties*
			dynamicProperties()
			{
				return &mDynamicProperties;
			}


			/**
			 * @brief Grants read-only access to topic dynamic properties
			 * @return dynamic properties package
			 */
			virtual
			const dds::AbstractTopic::DynamicProperties*
			constDynamicProperties() const
			{
				return &mDynamicProperties;
			}


		protected:
			std::string msKey=std::string();                          ///< key value
			dds::AbstractTopic::DynamicProperties mDynamicProperties; ///< properties package

	};

}
