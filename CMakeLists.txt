cmake_minimum_required(VERSION 3.5.1)
project(offer)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(3rdparty/googletest)
include_directories(3rdparty/googletest/googletest/include)

set(all_srcs "")
file(GLOB_RECURSE srcs ${CMAKE_SOURCE_DIR}/ch02/*.cpp)
list(APPEND all_srcs ${srcs})
file(GLOB_RECURSE srcs ${CMAKE_SOURCE_DIR}/ch03/*.cpp)
list(APPEND all_srcs ${srcs})
add_executable(test.bin main.cpp ${all_srcs})
target_link_libraries(test.bin gtest)
