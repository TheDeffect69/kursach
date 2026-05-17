cmake_minimum_required(VERSION 3.10)
project(EquipmentManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

add_executable(EquipmentManager
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/equipment.h
    src/equipmentdialog.cpp
    src/equipmentdialog.h
)

target_link_libraries(EquipmentManager PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
