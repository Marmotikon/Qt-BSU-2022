cmake_minimum_required(VERSION 3.21)
project(Lab_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Lab_4 main.cpp ray.cpp ray.h polygon.cpp polygon.h controller.cpp controller.h main_window.cpp main_window.h paint_widget.cpp paint_widget.h constants.h)
target_link_libraries(Lab_4
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

