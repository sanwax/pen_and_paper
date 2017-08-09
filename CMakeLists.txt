##
## Setup project basics
##
CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(pen_and_paper)
SET(CMAKE_CXX_STANDARD 14)


##
## Define output locations
##
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
IF (DEFINED WIN32 OR DEFINED WIN64)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
ELSE()
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
ENDIF()


##
## Qt5 is mandatory
##
FIND_PACKAGE(Qt5 5.8.0 CONFIG REQUIRED Core Gui Widgets Network Multimedia WebSockets)
IF    (NOT Qt5_FOUND)
	MESSAGE(FATAL_ERROR "[CMAKE] This application requires Qt5.")
ENDIF (NOT Qt5_FOUND)


##
## Filter Qt include directories so that Qt sublibraries are not included (e.g. /usr/include/qt
## but not /usr/include/qt/QtCore)
##
FOREACH (__arg ${Qt5Core_INCLUDE_DIRS})
	GET_FILENAME_COMPONENT(__name ${__arg} NAME)
	IF (NOT __name STREQUAL "QtCore")
		MESSAGE("[CMAKE] Adding Qt include directory: " ${__arg})
		INCLUDE_DIRECTORIES(${__arg})
	ENDIF()
ENDFOREACH()


##
## Add src directory as include paths
##
INCLUDE_DIRECTORIES(src)


##
## Walk subdirectories and build targets inside
##
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(experiments)
