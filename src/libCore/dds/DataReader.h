#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <libCore/dds/TopicType.h>
#include <libCore/dds/Operation.h>


namespace core
{
	namespace dds
	{

		class AbstractTopic;
		class TopicExchange;


		class DataReader
		{
			public:
				typedef std::function<void(const core::dds::TopicType,const std::shared_ptr<const core::dds::AbstractTopic>&,const core::dds::Operation op)> Callback;


				/**
				 * @brief Constructor
				 * @param [in] pExchange controller to work with
				 */
				DataReader(std::shared_ptr<core::dds::TopicExchange> pExchange);


				/**
				 * @brief Destructor
				 */
				virtual
				~DataReader();


				/**
				 * @brief This function receives events from the topic exchange
				 * @param [in] type of topic to handle
				 * @param [in] pTopic topic to distribute
				 * @param [in] operation kind
				 */
				virtual
				void
				handleEvent(const core::dds::TopicType type,std::shared_ptr<const core::dds::AbstractTopic> pTopic,const core::dds::Operation operation);


				/**
				 * @brief Subscribe a topic type, get called on any event
				 * @param [in] type of topic to subscribe
				 * @param [in] callback function to call on events
				 */
				virtual
				void
				subscribe(const core::dds::TopicType type,Callback callback);


				/**
				 * @brief Unsubscribe a specific topic
				 * @param [in] type of topic to unsubscribe
				 */
				virtual
				void
				unsubscribe(const core::dds::TopicType type);


				/**
				 * @brief Unsubscribe from all topics
				 */
				virtual
				void
				unsubscribe();


			protected:
				std::shared_ptr<core::dds::TopicExchange> mpExchange;                      ///< the topic exchange
				std::unordered_multimap<core::dds::TopicType,Callback> mCallbackMap;   ///< mapped callbacks
		};

	}
}
