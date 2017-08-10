#include <gtest/gtest.h>

namespace core
{
	namespace test
	{


		void init()
		{
			static int i = 0;
		}


		TEST(core_FactoryHolding, TriggerTest)
		{
			EXPECT_EQ(1, 1) << "Must work!";
		}


	}
}
