find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(BMX_HOME $ENV{BMX_HOME})
message(STATUS "BMX home: ${BMX_HOME}")

# libavcodec
pkg_check_modules(PC_bmx QUIET bmx)

find_path(bmx_INCLUDE_DIR
        NAMES bmx/BMXTypes.h
        PATHS ${PC_bmx_INCLUDE_DIRS} ${BMX_HOME}
        PATH_SUFFIXES include
        )

find_library(bmx_LIBRARY
        NAMES bmx
        PATHS ${PC_bmx_LIBRARY_DIRS} ${BMX_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(bmx
        FOUND_VAR bmx_FOUND
        REQUIRED_VARS
        bmx_LIBRARY
        bmx_INCLUDE_DIR
        VERSION_VAR bmx_VERSION
        )


if (bmx_FOUND AND NOT TARGET MXF::bmx)
    add_library(MXF::bmx UNKNOWN IMPORTED)
    set_target_properties(MXF::bmx PROPERTIES
            IMPORTED_LOCATION "${bmx_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_bmx_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${bmx_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        bmx_INCLUDE_DIR
        bmx_LIBRARY
)

set(bmx_VERSION_STRING ${bmx_VERSION})
