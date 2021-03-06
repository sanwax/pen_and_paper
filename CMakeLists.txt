##
## Setup project basics
##
CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(pen_and_paper)
SET(CMAKE_CXX_STANDARD 14)
ENABLE_TESTING()


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
## Locate google test library
##
SET(HAVE_GTEST 0)
FIND_LIBRARY(LIB_GTEST NAME gtest PATH_SUFFIXES gtest)
IF (NOT LIB_GTEST)
	MESSAGE(AUTHOR_WARNING "[CMAKE] Google test library not found - tests will be unavailable.")
ELSE()
	FIND_FILE(__GTEST_INC NAME gtest.h PATH_SUFFIXES gtest)
	IF (NOT __GTEST_INC)
		MESSAGE(AUTHOR_WARNING "[CMAKE] Google test library header not found - tests will be unavailable.")
	ELSE()
		GET_FILENAME_COMPONENT(__GTEST_PATH ${__GTEST_INC} PATH)
		INCLUDE_DIRECTORIES(${__GTEST_PATH})
		SET(HAVE_GTEST 1)
	ENDIF()
ENDIF()


##
## Qt5 is mandatory
##
FIND_PACKAGE(Qt5 5.8.0 CONFIG REQUIRED Core Gui Widgets Network Multimedia WebSockets)
IF    (NOT Qt5_FOUND)
	MESSAGE(FATAL_ERROR "[CMAKE] This application requires Qt5.")
ENDIF (NOT Qt5_FOUND)


MESSAGE("[CMAKE] --------------------------------------------------------------------")
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
MESSAGE("[CMAKE] HAVE_GTEST = " ${HAVE_GTEST} "   ( " ${LIB_GTEST} " )")
MESSAGE("[CMAKE] --------------------------------------------------------------------")


##
## Add src directory as include paths
##
INCLUDE_DIRECTORIES(src)


##
## Walk subdirectories and build targets inside
##
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(experiments)
ADD_SUBDIRECTORY(tests)
