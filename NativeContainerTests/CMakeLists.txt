cmake_minimum_required(VERSION 3.0)
project(NativeContainerTests)

add_library(odr OBJECT odr.cpp)
add_executable(NativeContainerTests
        $<TARGET_OBJECTS:odr>
        CommandTests.cpp)