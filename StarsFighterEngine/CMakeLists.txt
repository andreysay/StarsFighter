cmake_minimum_required(VERSION 3.28)

project(StarsFighter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${STARSFIGHTER_ENGINE_TARGET_NAME} STATIC
  include/framework/GameBaseApp.hpp
  src/framework/GameBaseApp.cpp

  include/GameEntry.hpp
  src/GameEntry.cpp

  include/framework/Core.hpp
  src/framework/Core.cpp

  src/helpers/Logger.cpp
  include/helpers/Logger.hpp

  include/framework/World.hpp
  src/framework/World.cpp

  include/framework/Actor.hpp
  src/framework/Actor.cpp
  
  include/framework/Object.hpp
  src/framework/Object.cpp
  
  include/framework/AssetManager.hpp
  src/framework/AssetManager.cpp)

target_include_directories(${STARSFIGHTER_ENGINE_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${STARSFIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${STARSFIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${STARSFIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${STARSFIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-audio)
