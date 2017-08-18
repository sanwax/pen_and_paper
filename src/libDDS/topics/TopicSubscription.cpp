#include <libDDS/ExceptionUnimplemented.h>
#include <libDDS/topics/TopicSubscription.h>


namespace dds
{
	namespace topics
	{
		static constexpr char __TYPE_NAME[] = "dds/topics/TopicSubscription";


		TopicType
		TopicSubscription::type() const
		{
			return dds::topicTypeNameToNumeric(__TYPE_NAME);
		}


		const char *
		TopicSubscription::typeName() const
		{
			return __TYPE_NAME;
		}


		bool
		TopicSubscription::canSerialize(const dds::SerializationFormat format) const noexcept
		{
			return false;
		}

		void
		TopicSubscription::serialize(std::shared_ptr<dds::SerializationContainer> pContainer) const
		{
			throw dds::ExceptionUnimplemented(__PRETTY_FUNCTION__, __FILE__, __LINE__);
		}

		void
		TopicSubscription::deserialize(std::shared_ptr<const dds::SerializationContainer> pContainer)
		{
			throw dds::ExceptionUnimplemented(__PRETTY_FUNCTION__, __FILE__, __LINE__);
		}


	}
}
