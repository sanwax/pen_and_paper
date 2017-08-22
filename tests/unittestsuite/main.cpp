#include <gtest/gtest.h>
#include <libCore/test/test.h>
#include <libDDS/test/DDS.gtest.h>


int
main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	//initialize test libs
	core::test::testFactoryHolding();
	dds::test::testTopicExchange();
	//run em
	return RUN_ALL_TESTS();
}
