cmake_minimum_required(VERSION 3.28.3)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_library(UI STATIC mainwindow.cpp mainwindow.h mainwindow.ui)

target_include_directories(UI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                     ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "UI binary dir: ${CMAKE_CURRENT_BINARY_DIR}")


target_link_libraries(UI PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)
