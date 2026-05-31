cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(TicTacToe LANGUAGES CXX)

option(QML_EXTRAS_SHARED "Build QmlExtras as a shared lib" OFF)

if(IOS)
    # prevent cmake install from breaking code signing
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif()

set(VERSION "0.1")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.9)

add_subdirectory(ResultChecker)

add_subdirectory(QmlExtras)

add_subdirectory(TicTacToe)
