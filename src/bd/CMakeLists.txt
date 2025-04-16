cmake_minimum_required(VERSION 3.28.3)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

add_library(bd STATIC
        Connector.h
        Connector.cpp
        IGenericDao.h
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLCIPHER REQUIRED sqlcipher)

target_link_libraries(bd PUBLIC ${SQLCIPHER_LIBRARIES})

target_include_directories(bd PUBLIC ${SQLCIPHER_INCLUDE_DIRS})
