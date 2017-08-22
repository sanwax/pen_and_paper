IF (HAVE_GTEST)


	##
	## Combine tests in a library to run all unit tests at once
	##
	SET(SOURCES
			DDS.gtest.h
			TopicExchangeTest.cpp)

	ADD_LIBRARY(DDS.gtest STATIC ${SOURCES})
	TARGET_LINK_LIBRARIES(DDS.gtest ${LIB_GTEST})
	TARGET_LINK_LIBRARIES(DDS.gtest DDS)


ENDIF (HAVE_GTEST)




ADD_EXECUTABLE(DDS.inspectTopic inspectTopic.cpp DDS.gtest.h)
TARGET_LINK_LIBRARIES(DDS.inspectTopic DDS)
