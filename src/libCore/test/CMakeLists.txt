IF (HAVE_GTEST)

  SET(SOURCES
    FactoryHoldingTest.cpp
  )

  ADD_LIBRARY(Core.gtest STATIC ${SOURCES})
  TARGET_LINK_LIBRARIES(Core.gtest Core)


ENDIF(HAVE_GTEST)
