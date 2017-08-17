SET(SOURCES
	SerializationFormat.h
	Operation.h
	AbstractTopic.h
	TopicType.h
	DataWriter.h
	DataWriter.cpp
	DataReader.h
	DataReader.cpp
	stl/convenience.h
	)

ADD_LIBRARY(DDS SHARED ${SOURCES})

ADD_SUBDIRECTORY(test)
