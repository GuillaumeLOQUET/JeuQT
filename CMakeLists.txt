cmake_minimum_required(VERSION 3.7)
project(JeuQT)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

add_executable(JeuQT main.cpp MainWindow.cpp RunScene.cpp Player.cpp Launcher.cpp)

target_link_libraries(JeuQT Qt5::Widgets)