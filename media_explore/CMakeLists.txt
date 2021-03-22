cmake_minimum_required(VERSION 3.15)
project(media_explore_proj)

find_package(FFmpeg REQUIRED)
#find_package(media_common)

add_executable(
        media_explore_run

        media_explore_main.cpp

        include/MediaSource.hpp
        src/MediaSource.cpp

        include/printable_errors.hpp
        src/printable_errors.cpp

        include/DurationRule.hpp
        src/DurationRule.cpp

        include/SequenceOfValuesChecker.hpp
        src/SequenceOfValuesChecker.cpp

        include/ValueCounter.hpp

        include/CheckReport.hpp
        src/CheckReport.cpp
)

target_link_libraries(
        media_explore_run
        PRIVATE
        ${FFMPEG_LIBRARIES}
)

target_include_directories(
        media_explore_run
        PRIVATE
        include
        ${FFMPEG_INCLUDE_DIRS}
)