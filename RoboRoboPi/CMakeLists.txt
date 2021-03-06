cmake_minimum_required(VERSION 3.6)
include(CheckCXXCompilerFlag)

project(RoboRoboPi CXX)

CHECK_CXX_COMPILER_FLAG(-std=c++1z HAS_CXX17_FLAG)

if(HAS_CXX17_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
else()
    message( FATAL_ERROR "Support for C++17 is required." )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Os")

set(AUDIO_SOURCE_FILES
  audio/AlsaSoundPlayer.cpp
  audio/SoundPlayer_linux.cpp
  audio/SoundPlayerFactory.cpp
  audio/SpeechSynthesizerFactory.cpp
  audio/SpeechSynthesizerTts.cpp
)

set(COMMANDS_SOURCE_FILES
  commands/HelpCommand.cpp
  commands/LedCommand.cpp
  commands/PlaySoundCommand.cpp
  commands/ServoCommand.cpp
  commands/TellCommand.cpp
  commands/UnknownCommand.cpp
)

set(SOURCE_FILES 
  ${AUDIO_SOURCE_FILES}
  ${COMMANDS_SOURCE_FILES}
  ConnectionListener.cpp
  logger.cpp
  main.cpp
  MessageHandler.cpp
  RoboRoboFactory.cpp
  RoboRobo.cpp
  GpioPi.cpp
  GpioFactory.cpp
  xmppComponent.cpp
  Servo.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


file(COPY sounds DESTINATION .)
add_executable(RoboRoboPi ${SOURCE_FILES})
target_link_libraries(RoboRoboPi /usr/local/lib/libpigpio.so)
target_link_libraries(RoboRoboPi -lpthread)
target_link_libraries(RoboRoboPi -lgloox)
target_link_libraries(RoboRoboPi ${CMAKE_CURRENT_SOURCE_DIR}/../picotts/libtts.a)
target_link_libraries(RoboRoboPi -lasound)
target_link_libraries(RoboRoboPi -lsndfile)
target_link_libraries(RoboRoboPi -lexpat)
target_link_libraries(RoboRoboPi -lstdc++fs)

