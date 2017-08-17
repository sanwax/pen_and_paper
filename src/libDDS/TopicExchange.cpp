
#include <libDDS/TopicExchange.h>


namespace dds
{

	TopicExchange::TopicExchange()
	{
		// TODO Auto-generated constructor stub

	}

	TopicExchange::~TopicExchange()
	{
		// TODO Auto-generated destructor stub
	}

	void TopicExchange::changeReader(dds::DataReader* pReader, dds::TopicType iTopicAdd, dds::TopicType iTopicRemove , bool bUnregister)
	{
	}

	void TopicExchange::changeWriter(dds::DataWriter* pWriter, dds::TopicType iTopicAdd, dds::TopicType iTopicRemove, bool bUnregister)
	{
	}

	void TopicExchange::publish(dds::DataWriter* pSender, std::unique_ptr<dds::AbstractTopic> pTopic)
	{
	}

	void TopicExchange::subscribe(dds::DataReader* pReceiver, dds::TopicType iType)
	{
	}

}

