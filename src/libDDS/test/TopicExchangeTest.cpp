#include <list>
#include <chrono>
#include <gtest/gtest.h>
#include <libDDS/test/DDS.gtest.h>
#include <libDDS/TopicExchange.h>
#include <libDDS/Participant.h>
#include <libDDS/topics/ParticipantRegistration.h>


using namespace std::chrono_literals;

namespace dds
{
	namespace test
	{

		void
		testTopicExchange()
		{
			static int i = 42;
		}


		class BufferingParticipant : public dds::Participant
		{
			public:
				/**
				 * @brief Constructor
				 * @param pExchange pointer to associated topic exchange
				 * @param sName labels the participant with a human readable name
				 */
				BufferingParticipant(std::shared_ptr<dds::AbstractTopicExchange> pExchange, const std::string &sName) : dds::Participant(pExchange, sName)
				{
				}


				/**
				 * @brief Topic exchange pushes a new topic activity
				 * @param pTopic the topic
				 * @param operation the activity
				 */
				virtual void
				handleTopicActivity(const std::shared_ptr<const dds::AbstractTopic> &pTopic, const dds::Operation operation) noexcept
				{
					mActivityList.push_back(std::make_tuple(pTopic, operation));
				}

				std::list<std::tuple<std::shared_ptr<const dds::AbstractTopic>, dds::Operation>> mActivityList;
		};


		TEST(dds_TopicExchange, StartStop)
		{
			dds::TopicExchange *pExchange = new dds::TopicExchange();
			std::this_thread::sleep_for(50ms);
			delete pExchange;
			pExchange = nullptr;
		}


		TEST(dds_TopicExchange, ParticipantRegistration)
		{
			//create exchange
			std::shared_ptr<dds::TopicExchange> pExchange = std::make_shared<dds::TopicExchange>();
			EXPECT_NE(pExchange->id(), 0);
			//create participant
			const std::string sParticipantName{"dds/test/ParticipantRegistration"};
			std::shared_ptr<dds::Participant> pParticipant = std::make_shared<dds::Participant>(pExchange, sParticipantName);
			//inspect participant
			EXPECT_NE(pParticipant->id(), 0);
			EXPECT_EQ(pParticipant->name(), sParticipantName);
			//give up participant
			pParticipant.reset();
			//give up topic exchange
			pExchange.reset();
		}


		TEST(dds_TopicExchange, PropagationTest)
		{
			//create exchange
			std::shared_ptr<dds::TopicExchange> pExchange = std::make_shared<dds::TopicExchange>();
			EXPECT_NE(pExchange->id(), 0);
			//create participant
			const std::string sParticipantName{"dds/test/PropagationTest1"};
			std::shared_ptr<dds::Participant> pParticipant1 = std::make_shared<dds::Participant>(pExchange, sParticipantName);
			EXPECT_NE(pParticipant1->id(), 0);
			//create buffering participant
			std::shared_ptr<BufferingParticipant> pParticipant2 = std::make_shared<BufferingParticipant>(pExchange, "dds/test/PropagationTest2");
			//wait for unwanted propagation
			std::this_thread::sleep_for(50ms);
			EXPECT_EQ(pParticipant2->mActivityList.empty(), true);
			//subscribe topic without replay
			pParticipant2->subscribe(topics::ParticipantRegistration().type(), false);
			//wait for propagation
			std::this_thread::sleep_for(50ms);
			EXPECT_EQ(pParticipant2->mActivityList.empty(), true);
			pParticipant2->unsubscribe(topics::ParticipantRegistration().type());
			//resubscribe topic, this time with replay
			pParticipant2->subscribe(topics::ParticipantRegistration().type(), true);
			//wait for propagation
			std::this_thread::sleep_for(50ms);
			EXPECT_EQ(pParticipant2->mActivityList.size(), 2);
			//inspect the activities
			EXPECT_NE(std::get<0>(pParticipant2->mActivityList.front()).get(), nullptr);
			EXPECT_NE(std::get<0>(pParticipant2->mActivityList.back()).get(), nullptr);
			EXPECT_EQ(std::get<1>(pParticipant2->mActivityList.front()), dds::Operation::REPLAY);
			EXPECT_EQ(std::get<1>(pParticipant2->mActivityList.back()), dds::Operation::REPLAY);
			EXPECT_EQ(std::get<0>(pParticipant2->mActivityList.front())->type(), topics::ParticipantRegistration().type());
			EXPECT_EQ(std::get<0>(pParticipant2->mActivityList.back())->type(), topics::ParticipantRegistration().type());
			//fetch topics and order them by clock
			std::list<std::shared_ptr<const dds::AbstractTopic>> sortedTopicList;
			sortedTopicList.push_back(std::get<0>(pParticipant2->mActivityList.front()));
			sortedTopicList.push_back(std::get<0>(pParticipant2->mActivityList.back()));
			sortedTopicList.sort([](std::shared_ptr<const dds::AbstractTopic> &lhs, std::shared_ptr<const dds::AbstractTopic> &rhs)
			               {
				               return (rhs->constDynamicProperties()->mSenderClock) < (lhs->constDynamicProperties()->mSenderClock);
			               });
			ASSERT_LT(sortedTopicList.back()->constDynamicProperties()->mSenderClock,sortedTopicList.front()->constDynamicProperties()->mSenderClock);
			EXPECT_EQ(sortedTopicList.back()->constDynamicProperties()->mSender,pParticipant1->id());
			EXPECT_EQ(sortedTopicList.front()->constDynamicProperties()->mSender,pParticipant2->id());
			EXPECT_EQ(sortedTopicList.back()->constDynamicProperties()->mSenderExchange,pExchange->id());
			EXPECT_EQ(sortedTopicList.front()->constDynamicProperties()->mSenderExchange,pExchange->id());
			EXPECT_NE(sortedTopicList.front()->key(),sortedTopicList.back()->key());
			EXPECT_EQ(sortedTopicList.back()->key(),dds::AbstractParticipant::idAsKeyString(pParticipant1->id()));
			EXPECT_EQ(sortedTopicList.front()->key(),dds::AbstractParticipant::idAsKeyString(pParticipant2->id()));
			//give up participants
			pParticipant1.reset();
			pParticipant2.reset();
			//give up topic exchange
			pExchange.reset();
		}

	}
}