cmake_minimum_required(VERSION 3.0.2)
project(advanced_data_structure C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -g -Wdelete-incomplete -DTHREADED")
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -Wno-packed-bitfield-compat")
ENDIF ()

IF (CMAKE_BUILD_TYPE STREQUAL "Release")
    MESSAGE("Cmake build type is ${CMAKE_BUILD_TYPE}, optimization level is set to O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
ELSE ()
    MESSAGE("Cmake build type is ${CMAKE_BUILD_TYPE}, optimization level is set to O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
ENDIF ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(AdvancedDataStructureGtest REQUIRED)
INCLUDE_DIRECTORIES(AFTER "src")

add_executable(advanced_data_structure src/main.cc)
set_target_properties(advanced_data_structure PROPERTIES LINKER_LANGUAGE CXX)

aux_source_directory(src/tests TEST_FILES)
add_executable(advanced_data_structure_unittest ${TEST_FILES})
target_include_directories(advanced_data_structure_unittest PRIVATE ${GTEST_INCLUDE_DIR} unittest)
target_include_directories(advanced_data_structure_unittest PRIVATE "src/tests" unittest)
target_link_libraries(advanced_data_structure_unittest ${GTEST_LIBRARY} pthread)

enable_testing()
add_test(unittest advanced_data_structure_unittest)

