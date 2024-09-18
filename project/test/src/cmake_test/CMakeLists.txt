cmake_minimum_required(VERSION 3.5.0)
project(CmakeTest VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "-g -std=c++11")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_executable(CmakeTest ${SRC})
target_link_libraries(CmakeTest test_lib)

message(STATUS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}")

add_subdirectory(test_lib)
