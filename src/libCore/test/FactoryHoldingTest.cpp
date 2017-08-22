#include <gtest/gtest.h>
#include <libCore/AbstractFactoryHolding.h>

namespace core
{
	namespace test
	{

		void testFactoryHolding()
		{
			static int i = 0;
		}


		class SquareFactory : public core::AbstractFactory<int, int>
		{
			public:
				int
				construct(const int &key) const
				{
					if (key >= 0 && key <= 2)
					{
						return key * key;
					}
					else
					{
						throw core::FactoryException("Invalid key.");
					}
				}


				std::unordered_set<int>
				capabilities() const noexcept
				{
					return {0, 1, 2};
				}
		};


		class QubicFactory : public core::AbstractFactory<int, int>
		{
			public:
				int
				construct(const int &key) const
				{
					if (key >= 0 && key <= 4)
					{
						return key * key * key;
					}
					else
					{
						throw core::FactoryException("Invalid key.");
					}
				}


				std::unordered_set<int>
				capabilities() const noexcept
				{
					return {0, 1, 2, 3, 4};
				}
		};


		TEST(core_FactoryHolding, EmptyHolding)
		{
			core::AbstractFactoryHolding<int, int> holding;
			EXPECT_EQ(holding.capabilities().size(), 0) << "An holding without factories has nothing to produce.";
			EXPECT_THROW(holding.construct(0), core::FactoryHoldingException) << "An holding without factories cannot produce key 0.";
		}


		TEST(core_FactoryHolding, Registration)
		{
			core::AbstractFactoryHolding<int, int> holding;
			//add null factory
			std::shared_ptr<core::AbstractFactory<int, int>> pNullFactory;
			EXPECT_THROW(holding.registerFactory(pNullFactory), core::FactoryHoldingException) << "Null factories are not allowed.";
			//add factories twice
			std::shared_ptr<SquareFactory> pSquareFactory = std::make_shared<SquareFactory>();
			holding.registerFactory(pSquareFactory);
			EXPECT_THROW(holding.registerFactory(pSquareFactory), core::FactoryHoldingException) << "Double registration attempt.";
			//add qubic factory
			std::shared_ptr<QubicFactory> pQubicFactory = std::make_shared<QubicFactory>();
			holding.registerFactory(pQubicFactory);
		}


		TEST(core_FactoryHolding, Production1)
		{
			//prepare holding
			core::AbstractFactoryHolding<int, int> holding;
			//first square then qubic factory
			holding.registerFactory(std::make_shared<SquareFactory>());
			holding.registerFactory(std::make_shared<QubicFactory>());
			//test capabilities
			std::unordered_set<int> expected_cap = {0, 1, 2, 3, 4};
			EXPECT_EQ(expected_cap, holding.capabilities());
			//test production
			for (int i = 0; i <= 2; ++i)
			{
				EXPECT_EQ(holding.construct(i), i * i);
			}
			for (int i = 3; i <= 4; ++i)
			{
				EXPECT_EQ(holding.construct(i), i * i * i);
			}
		}


		TEST(core_FactoryHolding, Production2)
		{
			//prepare holding
			core::AbstractFactoryHolding<int, int> holding;
			//first qubic then square factory
			holding.registerFactory(std::make_shared<QubicFactory>());
			holding.registerFactory(std::make_shared<SquareFactory>());
			//test capabilities
			std::unordered_set<int> expected_cap = {0, 1, 2, 3, 4};
			EXPECT_EQ(expected_cap, holding.capabilities());
			//test production
			for (int i = 0; i <= 4; ++i)
			{
				EXPECT_EQ(holding.construct(i), i * i * i);
			}
		}


	}
}
