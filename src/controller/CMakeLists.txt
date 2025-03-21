cmake_minimum_required(VERSION 3.30)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

add_library(controller STATIC
        )

target_include_directories(controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})