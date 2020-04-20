cmake_minimum_required(VERSION 3.7)
project(projetQT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets CONFIG REQUIRED)
file (GLOB_RECURSE CIR2_sceneview_src src/*.cpp src/*.h)
add_executable(projetQT mainWindow.cpp main.cpp MainScene.cpp AvatarItem.cpp)
target_link_libraries(projetQT Qt5::Widgets)