IF (HAVE_GTEST)


	##
	## Combine tests in a library to run all unit tests at once
	##
	SET(SOURCES
		test.h
		FactoryHoldingTest.cpp
		)

	ADD_LIBRARY(Core.gtest STATIC ${SOURCES})
	TARGET_LINK_LIBRARIES(Core.gtest ${LIB_GTEST})


	##
	## Add test executable and pass it to ctest
	##
	ADD_EXECUTABLE(Core.FactoryHolding.gtest main.cpp FactoryHoldingTest.cpp)
	TARGET_LINK_LIBRARIES(Core.FactoryHolding.gtest Core)
	TARGET_LINK_LIBRARIES(Core.FactoryHolding.gtest ${LIB_GTEST})
	ADD_TEST(NAME Core.FactoryHolding COMMAND Core.FactoryHolding.gtest)


ENDIF (HAVE_GTEST)
