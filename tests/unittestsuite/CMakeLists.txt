IF (HAVE_GTEST)

  SET(SOURCES
    main.cpp)

  ADD_EXECUTABLE(allUnitTests ${SOURCES})
  TARGET_LINK_LIBRARIES(allUnitTests Core.gtest)
  TARGET_LINK_LIBRARIES(allUnitTests DDS.gtest)
  TARGET_LINK_LIBRARIES(allUnitTests ${LIB_GTEST})

ENDIF()
