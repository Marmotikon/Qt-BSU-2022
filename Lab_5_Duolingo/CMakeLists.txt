cmake_minimum_required(VERSION 3.21)
project(Lab_5_Duolingo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/marmotikon/Proga_second_sem/Qt/6.2.3/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Lab_5_Duolingo main.cpp)
target_link_libraries(Lab_5_Duolingo
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

