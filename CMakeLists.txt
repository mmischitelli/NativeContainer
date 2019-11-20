cmake_minimum_required(VERSION 3.0)
project(NativeContainer)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/NativeContainer)

add_subdirectory(NativeContainerTests)