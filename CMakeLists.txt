cmake_minimum_required(VERSION 3.28.3)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(libs/Catch2)

configure_file(${CMAKE_SOURCE_DIR}/data/creation.sql
               ${CMAKE_BINARY_DIR}/data/creation.sql COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/passwords.sqlite
               ${CMAKE_BINARY_DIR}/data/passwords.sqlite COPYONLY)

target_link_libraries(${PROJECT_NAME}
    model
    bd
    impl
    UI
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
