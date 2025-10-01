cmake_minimum_required(VERSION 3.28)

project(${STARS_ENGINE_TARGET_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${STARS_ENGINE_TARGET_NAME} STATIC
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
  src/framework/AssetManager.cpp 
  
  include/framework/MathUtility.hpp
  src/framework/MathUtility.cpp 
  
  include/framework/PhysicsSystem.hpp
  src/framework/PhysicsSystem.cpp
  
  include/framework/HealthComponent.hpp
  src/framework/HealthComponent.cpp

  include/framework/Delegate.hpp
  src/framework/Delegate.cpp 
  
  include/VFX/Particle.hpp
  src/VFX/Particle.cpp

  include/VFX/Explosion.hpp
  src/VFX/Explosion.cpp

  include/framework/TimersHandler.hpp
  src/framework/TimersHandler.cpp

 include/gameplay/GameStage.hpp
 src/gameplay/GameStage.cpp
)

target_include_directories(${STARS_ENGINE_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(SFML_LIB_NAME SFML)

include(FetchContent)
FetchContent_Declare(${SFML_LIB_NAME}
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${STARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${STARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${STARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${STARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

set(BOX2D_LIB_NAME box2d)
FetchContent_Declare(${BOX2D_LIB_NAME}
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG v3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${STARS_ENGINE_TARGET_NAME} PUBLIC ${BOX2D_LIB_NAME})