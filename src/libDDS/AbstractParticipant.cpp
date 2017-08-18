#include <random>
#include <libDDS/AbstractParticipant.h>
#include <libDDS/TopicExchange.h>
#include <libDDS/Exception.h>


namespace dds
{

	/*static*/
	dds::ParticipantId
	AbstractParticipant::createParticipantId() noexcept
	{
		static std::random_device rand_dev;
		static std::mt19937 generator{rand_dev()};
		static std::uniform_int_distribution<dds::ParticipantId>  distribution{};
		return distribution(generator);
	}


	AbstractParticipant::AbstractParticipant(std::shared_ptr<dds::TopicExchange>& pExchange,const std::string& sName):
		mId(AbstractParticipant::createParticipantId()),
		msName(sName),
		mpExchange(pExchange)
	{
		//inspect pointer
		if (!mpExchange)
		{
			throw dds::Exception("Invalid topic exchange pointer: nullptr");
		}
		//register participant
	}


	/*virtual*/
	AbstractParticipant::~AbstractParticipant()
	{
		//unregister participant
	}

}