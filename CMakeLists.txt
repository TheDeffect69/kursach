cmake_minimum_required(VERSION 3.10)
project(EquipmentManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS Core5Compat REQUIRED)
endif()

add_executable(EquipmentManager
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/equipment.h
    src/equipmentdialog.cpp
    src/equipmentdialog.h
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(EquipmentManager PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Core5Compat)
else()
    target_link_libraries(EquipmentManager PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
endif()
