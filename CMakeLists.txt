cmake_minimum_required(VERSION 3.28)

project(StarsFighter VERSION 0.9.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_LIB_NAME SFML)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# The executable target name
set(STARSFIGHTER_ENGINE_TARGET_NAME StarsFighterEngine)
set(STARSFIGHTER_GAME_TARGET_NAME StarsFighterGame)

add_subdirectory(StarsFighterEngine)
add_subdirectory(StarsFighterGame)
