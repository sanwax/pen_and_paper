#pragma once

#include <memory>
#include <libCore/dds/AbstractTopic.h>
#include <libCore/dds/DataReader.h>
#include <libCore/dds/DataWriter.h>
#include <libCore/dds/Operation.h>


namespace core
{
	namespace dds
	{

		class TopicExchange
		{
			public:
				TopicExchange();


				virtual
				~TopicExchange();


				void
				changeReader(core::dds::DataReader* pReader,core::dds::TopicType iTopicAdd=0,core::dds::TopicType iTopicRemove=0,bool bUnregister=false);


				void
				changeWriter(core::dds::DataWriter* pWriter,core::dds::TopicType iTopicAdd=0,core::dds::TopicType iTopicRemove=0,bool bUnregister=false);

				void
				publish(core::dds::DataWriter* pSender,std::unique_ptr<core::dds::AbstractTopic> pTopic);


				void
				subscribe(core::dds::DataReader* pReceiver,core::dds::TopicType iType);

		};


	}
}
