cmake_minimum_required(VERSION 3.28)

project(StarsFighter VERSION 0.9.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# The executable target name
set(STARS_ENGINE_TARGET_NAME StarsEngine)
set(STARSFIGHTER_GAME_TARGET_NAME StarsFighter)

add_subdirectory(StarsEngine)
add_subdirectory(StarsFighterGame)
