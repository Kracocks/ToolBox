cmake_minimum_required(VERSION 3.28.3)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

add_library(impl STATIC
        IdentifiantDaoImpl.cpp
        IdentifiantDaoImpl.h
        TokenDaoImpl.cpp
        TokenDaoImpl.h
        ServiceDaoImpl.cpp
        ServiceDaoImpl.h
        DaoManager.h)

target_include_directories(impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
