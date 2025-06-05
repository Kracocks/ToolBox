cmake_minimum_required(VERSION 3.28.3)
project(SystemManager)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_library(UI STATIC mainwindow.cpp mainwindow.h mainwindow.ui
    connection.h connection.cpp connection.ui
    add_popups/addservice.h add_popups/addservice.cpp add_popups/addservice.ui
    loginswindow.h loginswindow.cpp loginswindow.ui
    add_popups/addlogin.h add_popups/addlogin.cpp add_popups/addlogin.ui
    tokenswindow.h tokenswindow.cpp tokenswindow.ui
    add_popups/addtoken.h add_popups/addtoken.cpp add_popups/addtoken.ui

    custom_widgets/showservicewidget.h custom_widgets/showservicewidget.cpp custom_widgets/showservicewidget.ui
    custom_widgets/flowlayout.h custom_widgets/flowlayout.cpp
)

target_include_directories(UI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                     ${CMAKE_CURRENT_BINARY_DIR}/UI_autogen/include)

target_link_libraries(UI PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets bd model impl)
