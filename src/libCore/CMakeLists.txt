SET(SOURCES
	Core.cpp
	AbstractComponent.h
	AbstractFactory.h
	AbstractException.h
	AbstractFactoryHolding.h
	dds/SerializationFormat.h
	dds/Operation.h
	dds/AbstractTopic.h
	dds/TopicType.h
	dds/DataWriter.h
	dds/DataWriter.cpp
	dds/DataReader.h
	dds/DataReader.cpp
	stl/convenience.h
	)

ADD_LIBRARY(Core SHARED ${SOURCES})

ADD_SUBDIRECTORY(test)
