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
## Locate google test library
##
FIND_LIBRARY(__HAVE_GTEST_LIB NAME gtest PATH_SUFFIXES gtest)
IF (__HAVE_GTEST_LIB-NOTFOUND)
	MESSAGE(AUTHOR_WARNING "[CMAKE] Google test library not found - tests will be unavailable.")
ENDIF()
FIND_FILE(__HAVE_GTEST_INC NAME gtest.h PATH_SUFFIXES gtest)
IF (__HAVE_GTEST_INC-NOTFOUND)
	MESSAGE(AUTHOR_WARNING "[CMAKE] Google test library header not found - tests will be unavailable.")
ELSE()
	GET_FILENAME_COMPONENT(__GTEST_PATH ${__HAVE_GTEST_INC} PATH)
	INCLUDE_DIRECTORIES(${__GTEST_PATH})
ENDIF()
IF (NOT (__HAVE_GTEST_LIB-NOTFOUND AND __HAVE_GTEST_INC-NOTFOUND))
	SET(HAVE_GTEST 1)
	SET(LIB_GTEST ${__HAVE_GTEST_LIB})
ELSE()
	SET(HAVE_GTEST 0)
	SET(LIB_GTEST "n/a")
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
