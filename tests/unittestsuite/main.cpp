#include <gtest/gtest.h>
#include <libCore/test/test.h>

int
main(int argc,char** argv)
{
  ::testing::InitGoogleTest(&argc,argv);
  //initialize test libs
  core::test::init();
  //run em
  return RUN_ALL_TESTS();
}
