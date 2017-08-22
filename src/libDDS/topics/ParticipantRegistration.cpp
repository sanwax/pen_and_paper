#include <iomanip>
#include <sstream>
#include <libDDS/AbstractParticipant.h>
#include <libDDS/topics/ParticipantRegistration.h>
#include <libDDS/ExceptionUnimplemented.h>


namespace dds
{
	namespace topics
	{
		static constexpr char __TYPE_NAME[] = "dds/topics/ParticipantRegistration";


		TopicType
		ParticipantRegistration::type() const
		{
			return dds::topicTypeNameToNumeric(__TYPE_NAME);
		}

		const char *
		ParticipantRegistration::typeName() const
		{
			return __TYPE_NAME;
		}

		bool
		ParticipantRegistration::canSerialize(const dds::SerializationFormat format) const noexcept
		{
			return false;
		}

		void
		ParticipantRegistration::serialize(std::shared_ptr<dds::SerializationContainer> pContainer) const
		{
			throw dds::ExceptionUnimplemented(__PRETTY_FUNCTION__, __FILE__, __LINE__);
		}

		void
		ParticipantRegistration::deserialize(std::shared_ptr<const dds::SerializationContainer> pContainer)
		{
			throw dds::ExceptionUnimplemented(__PRETTY_FUNCTION__, __FILE__, __LINE__);
		}


		void
		ParticipantRegistration::set(dds::AbstractParticipant *pParticipant)
		{
			if (pParticipant == nullptr)
			{
				throw Exception("Invalid participant: nullptr");
			}
			mParticipantId = pParticipant->id();
			mParticipantName = pParticipant->name();
			mpParticipant=pParticipant;
			std::stringstream s;
			s << std::hex << std::setfill('0') << std::setw(sizeof(mParticipantId) * 2) << mParticipantId;
			msKey = s.str();
		}

	}
}
