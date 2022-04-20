cmake_minimum_required(VERSION 3.22)
project(duolingo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_PREFIX_PATH "~/marmotikon/Proga_second_sem/Qt/6.2.3/gcc_64/lib/cmake")
set(CMAKE_PREFIX_PATH "~/Qt/6.3.0/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(duolingo
        main.cpp
        main_window.cpp
        abstract_controller.h
        controller.cpp
        model.cpp
        pick_an_option_widget.cpp
        input_answer_widget.cpp
        audio_widget.cpp
        main_page_widget.cpp
        resources.qrc)

target_link_libraries(duolingo
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )

