SET(SOURCES
		SerializationFormat.h
		Operation.h
		AbstractTopic.h
		TopicType.h
		#DataWriter.h
		#DataWriter.cpp
		#DataReader.h
		#DataReader.cpp
		Exception.h
		ExceptionUnimplemented.h
		AbstractTopicExchange.h
		stl/convenience.h
		topics/TopicSubscription.h
		topics/TopicSubscription.cpp
		topics/ParticipantRegistration.cpp
		topics/ParticipantRegistration.h
		MonotonicClock.h
		ParticipantId.h
		AbstractParticipant.h
		AbstractParticipant.cpp
		Participant.cpp
		Participant.h
		TopicExchange.cpp
		TopicExchange.h)

ADD_LIBRARY(DDS SHARED ${SOURCES})
TARGET_LINK_LIBRARIES(DDS pthread)

ADD_SUBDIRECTORY(test)
