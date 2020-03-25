cmake_minimum_required(VERSION 3.15)
project(media_decoding)

set(CMAKE_CXX_STANDARD 14)



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)  # Qt dependency

message(STATUS "Bin dir: ${CMAKE_CURRENT_BINARY_DIR}")


find_package(FFmpeg REQUIRED)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_executable(
        media_decoding
#        WIN32
        main.cpp

        media_explore/MediaExplorer.hpp
        media_explore/MediaExplorer.cpp

        transcode_audio/full_code.hpp

        ui/Window.hpp
        ui/Window.cpp

)


#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    set_property(TARGET main PROPERTY WIN32_EXECUTABLE true)
#endif()


target_link_libraries(
        media_decoding

        PUBLIC
        FFmpeg::libavcodec
        FFmpeg::libavutil
        FFmpeg::libavfilter
        FFmpeg::libavformat
        FFmpeg::libswresample
        FFmpeg::libswscale

        Qt5::Widgets
        Qt5::Multimedia

)