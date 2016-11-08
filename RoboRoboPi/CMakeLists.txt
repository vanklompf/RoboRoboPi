cmake_minimum_required(VERSION 3.6)
include(CheckCXXCompilerFlag)

project(RoboRoboPi CXX)

CHECK_CXX_COMPILER_FLAG(-std=c++1z HAS_CXX17_FLAG)

if(HAS_CXX17_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message( FATAL_ERROR "Support for C++17 is required." )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Os")

set(SOURCE_FILES 
AlsaPcmPlayer.cpp
ConnectionListener.cpp
Gpio.cpp
logger.cpp
main.cpp
MessageHandler.cpp
RoboRoboFactory.cpp
RoboRobo.cpp
servo.cpp
SoundPlayer_linux.cpp
SpeechSynthesizer_linux.cpp
xmppComponent.cpp
commands/HelpCommand.cpp
commands/LedCommand.cpp
commands/PlaySoundCommand.cpp
commands/ServoCommand.cpp
commands/TellCommand.cpp
commands/UnknownCommand.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


file(COPY sounds DESTINATION .)
add_executable(RoboRoboPi ${SOURCE_FILES})
target_link_libraries(RoboRoboPi /usr/local/lib/libpigpio.so)
target_link_libraries(RoboRoboPi -lwiringPi)
target_link_libraries(RoboRoboPi -lpthread)

target_link_libraries(RoboRoboPi -lgloox)

target_link_libraries(RoboRoboPi ${CMAKE_CURRENT_SOURCE_DIR}/../picotts/libtts.a)
target_link_libraries(RoboRoboPi -lasound)
target_link_libraries(RoboRoboPi -lexpat)

target_link_libraries(RoboRoboPi -lstdc++fs)

