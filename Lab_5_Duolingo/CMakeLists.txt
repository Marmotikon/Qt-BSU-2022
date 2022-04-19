cmake_minimum_required(VERSION 3.21)
project(duolingo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "~marmotikon/Proga_second_sem/Qt/6.2.3/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
#        Multimedia
        REQUIRED)

add_executable(duolingo
        main.cpp
        main_window.cpp
        main_window.h
        abstract_controller.h
        controller.cpp
        controller.h
        model.h model.cpp pick_an_option_widget.cpp pick_an_option_widget.h input_answer_widget.cpp input_answer_widget.h)

target_link_libraries(duolingo
        Qt::Core
        Qt::Gui
        Qt::Widgets
#        Qt::Multimedia
        )

