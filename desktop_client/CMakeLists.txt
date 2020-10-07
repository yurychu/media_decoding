cmake_minimum_required(VERSION 3.15)
project(desktop_client_proj)

set(CMAKE_INCLUDE_CURRENT_DIR ON)  # Qt dependency

##find_package(Qt5Widgets REQUIRED)
##find_package(Qt5Multimedia REQUIRED)
##find_package(Qt5MultimediaWidgets REQUIRED)
## or option too:
find_package(Qt5
        REQUIRED
        COMPONENTS
        Widgets Multimedia MultimediaWidgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  # User Interface Compiler (uic), read ui and create .h file.
set(CMAKE_AUTORCC ON)


# desktop-client
add_executable(
        dsk_client

#        WIN32  # to hide console appear

#        src/main.cpp
#        src/main2.cpp
#        src/simple_main.cpp
        src/cell_check_main.cpp

        src/ClientInterface.ui

        include/desktop_client/ExperimentWindow.hpp
        src/ExperimentWindow.cpp

        include/desktop_client/ClientWindow.hpp
        src/ClientWindow.cpp

        include/desktop_client/FindDialog.hpp
        src/FindDialog.cpp

        include/desktop_client/SimpleCode.hpp
        src/SimpleCode.cpp

)

target_include_directories(
        dsk_client
        PRIVATE
        include
)

target_link_libraries(
        dsk_client
        PUBLIC
        Qt5::Widgets
        Qt5::Multimedia
        Qt5::MultimediaWidgets

)
