cmake_minimum_required(VERSION 3.28)

project(${STARSFIGHTER_GAME_TARGET_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${STARSFIGHTER_GAME_TARGET_NAME}
  include/GameFramework/StarsFighterGame.hpp
  src/GameFramework/StarsFighterGame.cpp

  include/Spaceship/Spaceship.hpp
  src/Spaceship/Spaceship.cpp 
  
  include/Player/PlayerSpaceship.hpp
  src/Player/PlayerSpaceship.cpp
  
  include/Weapon/BulletShooter.hpp
  src/Weapon/BulletShooter.cpp

  include/Weapon/Shooter.hpp
  src/Weapon/Shooter.cpp 
  
  include/Weapon/Bullet.hpp
  src/Weapon/Bullet.cpp 

  include/Enemy/EnemySpaceship.hpp  
  src/Enemy/EnemySpaceship.cpp 

  include/Enemy/Vanguard.hpp
  src/Enemy/Vanguard.cpp

 include/Levels/Level_1.hpp
 src/Levels/Level_1.cpp

 include/Enemy/VanguardStage.hpp
 src/Enemy/VanguardStage.cpp)

target_include_directories(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC ${STARS_ENGINE_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
  TARGET ${STARSFIGHTER_GAME_TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
	${RESOURCE_SRC_DIR}
	$<TARGET_FILE_DIR:${STARSFIGHTER_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
  COMMENT "Copying resource folder to output directory"
)

configure_file(
  "Config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/Config.h" ESCAPE_QUOTES
)