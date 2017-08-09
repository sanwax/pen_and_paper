SET(SOURCES
	Core.cpp
	AbstractComponent.h
	AbstractFactory.h
	AbstractException.h
	AbstractFactoryHolding.h
	)

ADD_LIBRARY(Core SHARED ${SOURCES})
