cmake_minimum_required(VERSION 3.7)
project(pen_and_paper)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


FIND_PACKAGE(Qt5 5.8.0 CONFIG REQUIRED Core Gui Widgets Network Multimedia WebSockets)
IF    (NOT Qt5_FOUND)
	MESSAGE("++++ This application requires Qt5. ++++")
ENDIF (NOT Qt5_FOUND)
include_directories(/usr/include/qt)

ADD_SUBDIRECTORY(experiments)



INCLUDE_DIRECTORIES(.)
