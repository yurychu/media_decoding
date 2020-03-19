find_package(PkgConfig)
include(FindPackageHandleStandardArgs)

set(FFMPEG_HOME $ENV{FFMPEG_HOME})

# libavcodec
pkg_check_modules(PC_libavcodec QUIET libavcodec)

find_path(libavcodec_INCLUDE_DIR
        NAMES libavcodec/avcodec.h
        PATHS ${PC_libavcodec_INCLUDE_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES include
)

find_library(libavcodec_LIBRARY
        NAMES avcodec
        PATHS ${PC_libavcodec_LIBRARY_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES lib
)

find_package_handle_standard_args(libavcodec
        FOUND_VAR libavcodec_FOUND
        REQUIRED_VARS
        libavcodec_LIBRARY
        libavcodec_INCLUDE_DIR
        VERSION_VAR libavcodec_VERSION
)

if (libavcodec_FOUND AND NOT TARGET FFmpeg::libavcodec)
    add_library(FFmpeg::libavcodec UNKNOWN IMPORTED)
    set_target_properties(FFmpeg::libavcodec PROPERTIES
            IMPORTED_LOCATION "${libavcodec_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_libavcodec_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${libavcodec_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(
        libavcodec_INCLUDE_DIR
        libavcodec_LIBRARY
)

set(libavcodec_VERSION_STRING ${libavcodec_VERSION})


# libavdevice
pkg_check_modules(PC_libavdevice QUIET libavdevice)



# libavfilter
pkg_check_modules(PC_libavfilter QUIET libavfilter)

find_path(libavfilter_INCLUDE_DIR
        NAMES libavfilter/avfilter.h
        PATHS ${PC_libavfilter_INCLUDE_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES include
        )

find_library(libavfilter_LIBRARY
        NAMES avfilter
        PATHS ${PC_libavfilter_LIBRARY_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(libavfilter
        FOUND_VAR libavfilter_FOUND
        REQUIRED_VARS
        libavfilter_LIBRARY
        libavfilter_INCLUDE_DIR
        VERSION_VAR libavfilter_VERSION
        )

if (libavfilter_FOUND AND NOT TARGET FFmpeg::libavfilter)
    add_library(FFmpeg::libavfilter UNKNOWN IMPORTED)
    set_target_properties(FFmpeg::libavfilter PROPERTIES
            IMPORTED_LOCATION "${libavfilter_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_libavfilter_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${libavfilter_INCLUDE_DIR}"
            )
endif()

mark_as_advanced(
        libavfilter_INCLUDE_DIR
        libavfilter_LIBRARY
)
set(libavfilter_VERSION_STRING ${libavfilter_VERSION})


# libavformat
pkg_check_modules(PC_libavformat QUIET libavformat)

find_path(libavformat_INCLUDE_DIR
        NAMES libavformat/avformat.h
        PATHS ${PC_libavformat_INCLUDE_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES include
        )

find_library(libavformat_LIBRARY
        NAMES avformat
        PATHS ${PC_libavformat_LIBRARY_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(libavformat
        FOUND_VAR libavformat_FOUND
        REQUIRED_VARS
        libavformat_LIBRARY
        libavformat_INCLUDE_DIR
        VERSION_VAR libavformat_VERSION
        )

if (libavformat_FOUND AND NOT TARGET FFmpeg::libavformat)
    add_library(FFmpeg::libavformat UNKNOWN IMPORTED)
    set_target_properties(FFmpeg::libavformat PROPERTIES
            IMPORTED_LOCATION "${libavformat_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_libavformat_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${libavformat_INCLUDE_DIR}"
            )
endif()

mark_as_advanced(
        libavformat_INCLUDE_DIR
        libavformat_LIBRARY
)
set(libavformat_VERSION_STRING ${libavformat_VERSION})


# libavutil
pkg_check_modules(PC_libavutil QUIET libavutil)

find_path(libavutil_INCLUDE_DIR
        NAMES libavutil/avutil.h
        PATHS ${PC_libavutil_INCLUDE_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES include
)

find_library(libavutil_LIBRARY
        NAMES avutil
        PATHS ${PC_libavutil_LIBRARY_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES lib
)

find_package_handle_standard_args(libavutil
        FOUND_VAR libavutil_FOUND
        REQUIRED_VARS
        libavutil_LIBRARY
        libavutil_INCLUDE_DIR
        VERSION_VAR libavutil_VERSION
)

if (libavutil_FOUND AND NOT TARGET FFmpeg::libavutil)
    add_library(FFmpeg::libavutil UNKNOWN IMPORTED)
    set_target_properties(FFmpeg::libavutil PROPERTIES
            IMPORTED_LOCATION "${libavutil_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_libavutil_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${libavutil_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(
        libavutil_INCLUDE_DIR
        libavutil_LIBRARY
)

set(libavutil_VERSION_STRING ${libavutil_VERSION})


# libpostproc
pkg_check_modules(PC_libpostproc QUIET libpostproc)



# libswresample
pkg_check_modules(PC_libswresample QUIET libswresample)

find_path(libswresample_INCLUDE_DIR
        NAMES libswresample/swresample.h
        PATHS ${PC_libswresample_INCLUDE_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES include
        )

find_library(libswresample_LIBRARY
        NAMES swresample
        PATHS ${PC_libswresample_LIBRARY_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(libswresample
        FOUND_VAR libswresample_FOUND
        REQUIRED_VARS
        libswresample_LIBRARY
        libswresample_INCLUDE_DIR
        VERSION_VAR libswresample_VERSION
        )

if (libswresample_FOUND AND NOT TARGET FFmpeg::libswresample)
    add_library(FFmpeg::libswresample UNKNOWN IMPORTED)
    set_target_properties(FFmpeg::libswresample PROPERTIES
            IMPORTED_LOCATION "${libswresample_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_libswresample_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${libswresample_INCLUDE_DIR}"
            )
endif()

mark_as_advanced(
        libswresample_INCLUDE_DIR
        libswresample_LIBRARY
)

set(libswresample_VERSION_STRING ${libswresample_VERSION})


# libswscale
pkg_check_modules(PC_libswscale QUIET libswscale)

find_path(libswscale_INCLUDE_DIR
        NAMES libswscale/swscale.h
        PATHS ${PC_libswscale_INCLUDE_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES include
        )

find_library(libswscale_LIBRARY
        NAMES swscale
        PATHS ${PC_libswscale_LIBRARY_DIRS} ${FFMPEG_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(libswscale
        FOUND_VAR libswscale_FOUND
        REQUIRED_VARS
        libswscale_LIBRARY
        libswscale_INCLUDE_DIR
        VERSION_VAR libswscale_VERSION
        )

if (libswscale_FOUND AND NOT TARGET FFmpeg::libswscale)
    add_library(FFmpeg::libswscale UNKNOWN IMPORTED)
    set_target_properties(FFmpeg::libswscale PROPERTIES
            IMPORTED_LOCATION "${libswscale_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_libswscale_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${libswscale_INCLUDE_DIR}"
            )
endif()

mark_as_advanced(
        libswscale_INCLUDE_DIR
        libswscale_LIBRARY
)

set(libswscale_VERSION_STRING ${libswscale_VERSION})
