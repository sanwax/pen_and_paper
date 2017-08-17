
#include <libCore/dds/Exception.h>
#include <libCore/dds/DataReader.h>
#include <libCore/dds/TopicExchange.h>
#include <libCore/dds/AbstractTopic.h>
#include <libCore/stl/convenience.h>


namespace core
{
	namespace dds
	{


		DataReader::DataReader(std::shared_ptr<core::dds::TopicExchange> pExchange):
			mpExchange(pExchange),
			mCallbackMap()
		{
			if (!mpExchange)
			{
				throw Exception("Invalid topic exchange: nullptr.");
			}
			mpExchange->changeReader(this);
		}


		/*virtual*/
		DataReader::~DataReader()
		{
			unsubscribe();
			mpExchange->changeReader(this,0,0,true);
		}


		/*virtual*/
		void
		DataReader::handleEvent(const core::dds::TopicType type,std::shared_ptr<const core::dds::AbstractTopic> pTopic,const core::dds::Operation operation)
		{
			auto range=mCallbackMap.equal_range(type);
			while (range.first!=range.second)
			{
				range.first->second(type,pTopic,operation);
				++range.first;
			}
		}


		/*virtual*/
		void
		DataReader::subscribe(const core::dds::TopicType type,Callback callback)
		{
			//test if topic is already known
			if (mCallbackMap.find(type)!=mCallbackMap.end())
			{
				mCallbackMap.insert(std::make_pair(type,callback));
			}
			//not yet registered topic
			mCallbackMap.insert(std::make_pair(type,callback));
			mpExchange->changeReader(this,type);
		}


		/*virtual*/
		void
		DataReader::unsubscribe(const core::dds::TopicType type)
		{
			if (mCallbackMap.find(type)!=mCallbackMap.end())
			{
				mpExchange->changeReader(this,0,type);
				mCallbackMap.erase(type);
			}
		}


		/*virtual*/
		void
		DataReader::unsubscribe()
		{
			while (mCallbackMap.empty()==false)
			{
				auto it=mCallbackMap.begin();
				auto key=it->first;
				mpExchange->changeReader(this,0,key);
				mCallbackMap.erase(key);
		}
	}


	}
}
