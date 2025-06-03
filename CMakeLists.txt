cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)
include_directories(src/include)

###############################################################################
# SFML 3.0 - Build locally from ./SFML
###############################################################################

set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_USE_SYSTEM_DEPS OFF)

add_subdirectory(SFML EXCLUDE_FROM_ALL)

###############################################################################
# Executable & sources
###############################################################################

add_executable(${MAIN_EXECUTABLE_NAME}
    main.cpp
    src/src/SceneManager.cpp
    src/src/GameScene.cpp
    src/src/MenuScene.cpp
    src/src/Button.cpp
    src/src/ResourceManager.cpp
    src/src/Player.cpp
    src/src/Enemy.cpp
)

set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################
# Includes & linking
###############################################################################

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)

target_link_libraries(${MAIN_EXECUTABLE_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)

###############################################################################
# Install target & copy files
###############################################################################

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})

if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
