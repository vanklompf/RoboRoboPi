cmake_minimum_required(VERSION 3.3)
include(CheckCXXCompilerFlag)

project(wiring CXX)

CHECK_CXX_COMPILER_FLAG(-std=c++11 HAS_CXX14_FLAG)
CHECK_CXX_COMPILER_FLAG(-std=c++14 HAS_CXX14_FLAG)

if(HAS_CXX14_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(HAS_CXX11_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SOURCE_FILES main.cpp servo.h servo.cpp)

add_executable(wiring ${SOURCE_FILES})
target_link_libraries(wiring -lwiringPi)
target_link_libraries(wiring -lpthread)