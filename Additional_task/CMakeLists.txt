cmake_minimum_required(VERSION 3.21)
project(Task_for_mark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Task_for_mark main.cpp main_window.cpp main_window.h paint_widget.cpp paint_widget.h)

target_link_libraries(Task_for_mark
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

