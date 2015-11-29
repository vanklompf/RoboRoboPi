cmake_minimum_required(VERSION 3.3)
project(wiring)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp servo.h servo.cpp)

add_executable(wiring ${SOURCE_FILES})
target_link_libraries(wiring -lwiringPi)
target_link_libraries(wiring -lpthread)