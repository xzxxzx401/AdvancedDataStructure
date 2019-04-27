# - Find gtest
# Find the gtest library and includes
#
# GTEST_INCLUDE_DIR - where to find header fils
# GTEST_LIBRARY - where to find libgtest.a
# GTEST_MAIN_LIBRARY - where to find libgtest_main.a

find_path(GTEST_INCLUDE_DIR
  NAMES gtest/gtest.h
  PATHS ${CMAKE_SOURCE_DIR}/third_party/googletest/output/include NO_DEFAULT_PATH)
IF(NOT GTEST_INCLUDE_DIR)
  MESSAGE(FATAL_ERROR "could not find gtest/gtest.h file")
ELSE()
  MESSAGE(STATUS "gtest/gtest.h: " ${GTEST_INCLUDE_DIR})
ENDIF()

find_library(GTEST_LIBRARY
  NAMES libgtest.a gtest
  PATHS ${CMAKE_SOURCE_DIR}/third_party/googletest/output/lib NO_DEFAULT_PATH)
IF(NOT GTEST_LIBRARY)
  MESSAGE(FATAL_ERROR "could not find gtest library")
ELSE()
  MESSAGE(STATUS "gtest library: " ${GTEST_LIBRARY})
ENDIF()

find_library(GTEST_MAIN_LIBRARY
  NAMES libgtest_main.a gtest_main
  PATHS ${CMAKE_SOURCE_DIR}/third_party/googletest/output/lib NO_DEFAULT_PATH)
IF(NOT GTEST_MAIN_LIBRARY)
  MESSAGE(FATAL_ERROR "could not find gtest_main library")
ELSE()
  MESSAGE(STATUS "gtest_main library: " ${GTEST_MAIN_LIBRARY})
ENDIF()

mark_as_advanced(GTEST_INCLUDE_DIR GTEST_LIBRARY GTEST_MAIN_LIBRARY)
