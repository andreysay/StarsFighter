cmake_minimum_required(VERSION 3.27)

project(StarsFighter VERSION 0.9.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

set(TS_FILES StarsFighter_en_US.ts)
# The executable target name
set(STARSFIGHTER_GAME_TARGET_NAME StarsFighterGame)

# add_executable(StarsFighterGame

#   ${TS_FILES}
# )
# target_link_libraries(StarsFighterGame Qt${QT_VERSION_MAJOR}::Core)

# if(COMMAND qt_create_translation)
#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# else()
#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# endif()

# include(GNUInstallDirs)
# install(TARGETS StarsFighterGame
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
add_subdirectory(StarsFighter)
