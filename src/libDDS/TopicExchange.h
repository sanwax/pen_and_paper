#pragma once

#include <memory>
#include <libDDS/AbstractTopic.h>
#include <libDDS/DataReader.h>
#include <libDDS/DataWriter.h>
#include <libDDS/Operation.h>

namespace dds
{
	
	class TopicExchange
	{
		public:
			TopicExchange();

			virtual
			~TopicExchange();

			void
			changeReader(dds::DataReader* pReader, dds::TopicType iTopicAdd = 0, dds::TopicType iTopicRemove = 0, bool bUnregister = false);

			void
			changeWriter(dds::DataWriter* pWriter, dds::TopicType iTopicAdd = 0, dds::TopicType iTopicRemove = 0, bool bUnregister = false);

			void
			publish(dds::DataWriter* pSender, std::unique_ptr<dds::AbstractTopic> pTopic);

			void
			subscribe(dds::DataReader* pReceiver, dds::TopicType iType);
			
	};

}
