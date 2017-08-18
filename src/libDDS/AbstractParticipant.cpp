#include <random>
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

}