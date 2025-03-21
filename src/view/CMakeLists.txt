cmake_minimum_required(VERSION 3.30)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

add_library(view STATIC
        )

target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})