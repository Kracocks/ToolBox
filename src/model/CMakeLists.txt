cmake_minimum_required(VERSION 3.28.3)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

add_library(model STATIC
        Service.cpp
        Service.h
        Identifiant.h
        Token.cpp
        Token.h
        Encrypt.cpp
        Encrypt.h
        Utils.h)

find_package(OpenSSL REQUIRED)

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(model PRIVATE OpenSSL::Crypto sqlcipher)
