cmake_minimum_required(VERSION 3.16)

project(StarsFighter LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TS_FILES StarsFighter_en_US.ts)

# add_executable(StarsFighterGame

#   ${TS_FILES}
# )
# target_link_libraries(StarsFighterGame Qt${QT_VERSION_MAJOR}::Core)

# if(COMMAND qt_create_translation)
#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# else()
#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
#find_package(${STARSFIGHTER_ENGINE_TARGET_NAME} REQUIRED COMPONENTS ${STARSFIGHTER_ENGINE_TARGET_NAME})

add_executable(${STARSFIGHTER_GAME_TARGET_NAME}
  include/GameFramework/StarsFighterGame.hpp
  src/GameFramework/StarsFighterGame.cpp

)

target_include_directories(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${STARSFIGHTER_GAME_TARGET_NAME} PUBLIC ${STARSFIGHTER_ENGINE_TARGET_NAME})

# include(GNUInstallDirs)
# install(TARGETS ${STARSFIGHTER_GAME_TARGET_NAME}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
