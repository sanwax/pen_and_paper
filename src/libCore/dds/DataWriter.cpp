
#include <libCore/dds/AbstractTopic.h>
#include <libCore/dds/DataWriter.h>
#include <libCore/dds/Exception.h>
#include <libCore/dds/TopicExchange.h>


namespace core
{
	namespace dds
	{

		/*explicit*/
		DataWriter::DataWriter(std::shared_ptr<core::dds::TopicExchange> pSwitch):
			mpExchange(pSwitch)
		{
			if (!mpExchange)
			{
				throw Exception("Invalid topic switch: nullptr.");
			}
			mpExchange->changeWriter(this);
		}


		/*virtual*/
		DataWriter::~DataWriter()
		{
			mpExchange->changeWriter(this,0,0,true);
		}


		void
		DataWriter::addTopic(const core::dds::TopicType iType)
		{
			if (mTopicSet.find(iType)==mTopicSet.end())
			{
				//topic not yet registered
				mpExchange->changeWriter(this,iType);
			}
		}


		void
		DataWriter::addTopic(std::unique_ptr<core::dds::AbstractTopic>& pTopic)
		{
			if (!pTopic)
			{
				throw Exception("Unexpected object: nullptr. Unable to obtain topic type.");
			}
			//add topic
			addTopic(pTopic->type());
			//then send update
			mpExchange->publish(this,std::move(pTopic));
		}


		void
		DataWriter::publish(std::unique_ptr<core::dds::AbstractTopic>& pTopic)
		{
			//test if topic pointer is valid at all
			if (!pTopic)
			{
				return;
			}
			//ensure topic is registered
			if (mTopicSet.find(pTopic->type())==mTopicSet.end())
			{
				addTopic(pTopic);
			}
			else
			{
				mpExchange->publish(this,std::move(pTopic));
			}
		}


		void
		DataWriter::deleteTopic(std::unique_ptr<core::dds::AbstractTopic>& pTopic)
		{
			if (!pTopic)
			{
				throw Exception("Unexpected object: nullptr. Unable to obtain topic type.");
			}
			const auto topicType=pTopic->type();
			//publish last update
			mpExchange->publish(this,std::move(pTopic));
			//then unregister
			mpExchange->changeWriter(this,0,topicType);
		}


		void
		DataWriter::deleteTopic(const core::dds::TopicType iType)
		{
			auto iter=mTopicSet.find(iType);
			if (iter!=mTopicSet.end())
			{
				mpExchange->changeWriter(this,0,iType);
				mTopicSet.erase(iter);
			}
		}

	}
}
