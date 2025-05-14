cmake_minimum_required(VERSION 3.28)

project(StarsFighter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${STARSFIGHTER_GAME_TARGET_NAME}
  include/GameFramework/StarsFighterGame.hpp
  src/GameFramework/StarsFighterGame.cpp

)

target_include_directories(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC ${STARSFIGHTER_ENGINE_TARGET_NAME})
