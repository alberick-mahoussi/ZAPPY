cmake_minimum_required(VERSION 3.12)
project(zappy_gui)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(raylib REQUIRED)

set(SOURCES
    src/main.cpp
    src/window.cpp
    src/playerAI.cpp
    src/Button.cpp
    src/Sound.cpp
    src/Protocole.cpp
    src/Server.cpp
    src/Parser.cpp
    src/Threads.cpp
)

add_executable(zappy_gui ${SOURCES})
target_link_libraries(zappy_gui raylib)
target_include_directories(zappy_gui PRIVATE include/)
