#include <libDDS/Participant.h>
#include <libDDS/Exception.h>
#include <libDDS/AbstractTopicExchange.h>
#include <libDDS/topics/ParticipantRegistration.h>


namespace dds
{

	Participant::Participant(std::shared_ptr<dds::AbstractTopicExchange> &pExchange, const std::string &sName):
		AbstractParticipant(),
		mId(AbstractParticipant::createParticipantId()),
		msName(sName),
	    mpExchange(pExchange)
	{
		//inspect pointer
		if (!mpExchange)
		{
			throw dds::Exception("Invalid topic exchange pointer: nullptr");
		}
		//publish
		auto p=std::make_unique<topics::ParticipantRegistration>();
		p->set(this);
		mpExchange->publish(mId,std::move(p));
	}


	/*virtual*/
	Participant::~Participant()
	{
		//unregister participant
		auto p=std::make_unique<topics::ParticipantRegistration>();
		p->set(this);
		mpExchange->unpublish(mId,std::move(p));
	}

}