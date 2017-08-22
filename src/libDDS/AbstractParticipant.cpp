#include <random>
#include <iomanip>
#include <sstream>
#include <libDDS/AbstractParticipant.h>


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


	void
	AbstractParticipant::handleTopicActivity(const std::shared_ptr<const dds::AbstractTopic>& pTopic,const dds::Operation operation) noexcept
	{
		//skip
	}

	/*static*/
	std::string
	AbstractParticipant::idAsKeyString(const dds::ParticipantId id)
	{
		std::stringstream s;
		s << std::hex << std::setfill('0') << std::setw(sizeof(id) * 2) << id;
		return s.str();
	}

}