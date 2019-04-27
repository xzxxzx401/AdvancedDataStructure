cmake_minimum_required(VERSION 3.0.2)
project(AdvancedDataStructure C CXX)

add_definitions(-DMETRICS_NOT_SUPPORTED)
#add_definitions(-DPRIVATE_TEST)
#add_definitions(-DPRIVATE_AGENT_TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -g -Wdelete-incomplete -DTHREADED")
IF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -Wno-packed-bitfield-compat")
ENDIF()

IF (CMAKE_BUILD_TYPE STREQUAL "Release")
    MESSAGE("Cmake build type is ${CMAKE_BUILD_TYPE}, optimization level is set to O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
ELSE()
    MESSAGE("Cmake build type is ${CMAKE_BUILD_TYPE}, optimization level is set to O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
ENDIF()

set(CMAKE_FIND_LIBRARY_SUFFIXES .a${CMAKE_FIND_LIBRARY_SUFFIXES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(AdvancedDataStructureGtest REQUIRED)

INCLUDE_DIRECTORIES(AFTER "." "src")

execute_process(COMMAND "src/gen_version.sh" "src/version.h"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

file(GLOB SLIST "src/slist/*.cc" "src/slist/*.h")

add_library(slist STATIC ${SLIST})

set_target_properties(slist PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(slist)

#add_executable(advances_data_structure ${SERVER_FILES})
#set_target_properties(advances_data_structure PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(advances_data_structure advances_data_structure_common)

aux_source_directory(src/tests TEST_FILES)
#aux_source_directory(src/tests/*.h TEST_FILES)
add_executable(advances_data_structure_unittest ${TEST_FILES})
target_include_directories(advances_data_structure_unittest PRIVATE ${GTEST_INCLUDE_DIR} unittest)
target_include_directories(advances_data_structure_unittest PRIVATE "src/test" unittest)
target_link_libraries(advances_data_structure_unittest
        slist
        ${GTEST_LIBRARY}
        pthread)

enable_testing()
add_test(unittest advances_data_structure_unittest)

#install(TARGETS advances_data_structure RUNTIME DESTINATION bin)
#install(CODE "execute_process(COMMAND \"cmake/installations/bin/advances_data_structure_run\" \"${CMAKE_INSTALL_PREFIX}/bin/advances_data_structure_run\" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})")
#
#install(FILES cmake/installations/conf/advances_data_structure_flags.conf DESTINATION conf)
#
#install(TARGETS advances_data_structure_unittest
#        RUNTIME DESTINATION test
#        )
#
#install(CODE "execute_process(COMMAND \"cmake/installations/test/test\" \"${CMAKE_INSTALL_PREFIX}/test/test\" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})")

