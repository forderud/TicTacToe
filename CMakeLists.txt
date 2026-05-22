cmake_minimum_required(VERSION 3.16)
project(Calqlatr LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.9)

add_subdirectory(calqlatr)
