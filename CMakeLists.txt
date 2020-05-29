cmake_minimum_required(VERSION 3.15)
project(media_decoding)

set(CMAKE_CXX_STANDARD 14)



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)  # Qt dependency

message(STATUS "Bin dir: ${CMAKE_CURRENT_BINARY_DIR}")
#set(CMAKE_LIBRARY_ARCHITECTURE ON)
#message(STATUS "Lib arch enable?: ${CMAKE_LIBRARY_ARCHITECTURE}")

find_package(FFmpeg REQUIRED)

#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Multimedia REQUIRED)
#find_package(Qt5MultimediaWidgets REQUIRED)
# or option too:
find_package(Qt5
        REQUIRED
        COMPONENTS
        Widgets Multimedia MultimediaWidgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  # User Interface Compiler (uic), read ui and create .h file.
set(CMAKE_AUTORCC ON)

find_package(
        OpenCV
        4.2 EXACT
        REQUIRED
)

add_executable(
        media_decoding
        main.cpp
        common/include/common/macro_c_extern.hpp
        common/include/common/Exceptionator.hpp
        common/src/Exceptionator.cpp
        common/include/common/LocalFile.hpp
        common/src/LocalFile.cpp
        common/include/common/ByteBuff.hpp
        common/src/ByteBuff.cpp

        media_explore/MediaExplorer.hpp
        media_explore/MediaExplorer.cpp

        transcode_audio/full_code.hpp
        transcode_audio/include/transcode_audio/PatchAvErr2Str.hpp
        transcode_audio/include/transcode_audio/OpenInputFile.hpp
        transcode_audio/src/OpenInputFile.cpp
        transcode_audio/include/transcode_audio/OpenOutputFile.hpp
        transcode_audio/src/OpenOutputFile.cpp
        transcode_audio/include/transcode_audio/InitPacket.hpp
        transcode_audio/src/InitPacket.cpp
        transcode_audio/include/transcode_audio/InitInputFrame.hpp
        transcode_audio/src/InitInputFrame.cpp
        transcode_audio/include/transcode_audio/InitResampler.hpp
        transcode_audio/src/InitResampler.cpp
        transcode_audio/include/transcode_audio/InitFifo.hpp
        transcode_audio/src/InitFifo.cpp
        transcode_audio/include/transcode_audio/WriteOutputFileHeader.hpp
        transcode_audio/src/WriteOutputFileHeader.cpp
        transcode_audio/include/transcode_audio/DecodeAudioFrame.hpp
        transcode_audio/src/DecodeAudioFrame.cpp
        transcode_audio/include/transcode_audio/InitConvertedSamples.hpp
        transcode_audio/src/InitConvertedSamples.cpp
        transcode_audio/include/transcode_audio/ConvertSamples.hpp
        transcode_audio/src/ConvertSamples.cpp
        transcode_audio/include/transcode_audio/AddSamplesToFifo.hpp
        transcode_audio/src/AddSamplesToFifo.cpp
        transcode_audio/include/transcode_audio/ReadDecodeConvertAndStore.hpp
        transcode_audio/src/ReadDecodeConvertAndStore.cpp
        transcode_audio/include/transcode_audio/AudioFrameEncoder.hpp
        transcode_audio/src/AudioFrameEncoder.cpp
        transcode_audio/include/transcode_audio/InitOutputFrame.hpp
        transcode_audio/src/InitOutputFrame.cpp
        transcode_audio/include/transcode_audio/LoadEncodeAndWrite.hpp
        transcode_audio/src/LoadEncodeAndWrite.cpp
        transcode_audio/include/transcode_audio/WriteOutputFileTrailer.hpp
        transcode_audio/src/WriteOutputFileTrailer.cpp
        transcode_audio/include/transcode_audio/run_example.hpp
        transcode_audio/src/run_example.cpp

        data_flow/include/data_flow/Flow.hpp
        data_flow/src/Flow.cpp

        mxf_exploring/include/mxf_exploring/BERLength.hpp
        mxf_exploring/include/mxf_exploring/ContinuityResult.hpp
        mxf_exploring/include/mxf_exploring/FileStream.hpp
        mxf_exploring/include/mxf_exploring/Hasher.hpp
        mxf_exploring/include/mxf_exploring/IndexTableSegment.hpp
        mxf_exploring/include/mxf_exploring/KLV.hpp
        mxf_exploring/include/mxf_exploring/ObjectsParser.hpp
        mxf_exploring/include/mxf_exploring/ParserBCD.hpp
        mxf_exploring/include/mxf_exploring/PartOfStream.hpp
        mxf_exploring/include/mxf_exploring/Stream.hpp
        mxf_exploring/include/mxf_exploring/SystemItem.hpp
        mxf_exploring/include/mxf_exploring/TimeCodeStamp.hpp

        mxf_exploring/BERLength.cpp
        mxf_exploring/ContinuityResult.cpp
        mxf_exploring/FileStream.cpp
        mxf_exploring/Hasher.cpp
        mxf_exploring/IndexTableSegment.cpp
        mxf_exploring/KLV.cpp
        mxf_exploring/ObjectsParser.cpp
        mxf_exploring/ParserBCD.cpp
        mxf_exploring/PartOfStream.cpp
        mxf_exploring/Stream.cpp
        mxf_exploring/SystemItem.cpp
        mxf_exploring/TimeCodeStamp.cpp

)


#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    set_property(TARGET main PROPERTY WIN32_EXECUTABLE true)
#endif()

target_include_directories(
        media_decoding
        PUBLIC
        common/include
        transcode_audio/include
        data_flow/include
        mxf_exploring/include
)

target_link_libraries(
        media_decoding

        PUBLIC
        FFmpeg::libavcodec
        FFmpeg::libavutil
        FFmpeg::libavfilter
        FFmpeg::libavformat
        FFmpeg::libswresample
        FFmpeg::libswscale

        ${OpenCV_LIBS}

)


# for compile ffmpeg lib
set_target_properties(
        media_decoding
        PROPERTIES
        COMPILE_FLAGS "-D__STDC_CONSTANT_MACROS"
)


# desktop-client
add_executable(
        dsk_client

#        WIN32  # to hide console appear

        desktop_client/src/main.cpp
#        desktop_client/src/main2.cpp

        desktop_client/src/ClientInterface.ui

        desktop_client/include/desktop_client/ExperimentWindow.hpp
        desktop_client/src/ExperimentWindow.cpp

        desktop_client/include/desktop_client/ClientWindow.hpp
        desktop_client/src/ClientWindow.cpp

        desktop_client/include/desktop_client/FindDialog.hpp
        desktop_client/src/FindDialog.cpp

)

target_include_directories(
        dsk_client
        PRIVATE
        desktop_client/include
)

target_link_libraries(
        dsk_client
        PUBLIC
        Qt5::Widgets
        Qt5::Multimedia
        Qt5::MultimediaWidgets

)
