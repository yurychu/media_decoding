find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(BMX_HOME $ENV{BMX_HOME})
message(STATUS "BMX home: ${BMX_HOME}")

# libavcodec
pkg_check_modules(PC_BMX QUIET BMX)

find_path(BMX_INCLUDE_DIR
        NAMES bmx/BMXTypes.h
        PATHS ${PC_BMX_INCLUDE_DIRS} ${BMX_HOME}
        PATH_SUFFIXES include
        )

find_library(BMX_LIBRARY
        NAMES bmx
        PATHS ${PC_BMX_LIBRARY_DIRS} ${BMX_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(BMX
        FOUND_VAR BMX_FOUND
        REQUIRED_VARS
        BMX_LIBRARY
        BMX_INCLUDE_DIR
        VERSION_VAR BMX_VERSION
        )


if (BMX_FOUND AND NOT TARGET MXF::bmx)
    add_library(MXF::bmx UNKNOWN IMPORTED)
    set_target_properties(MXF::bmx PROPERTIES
            IMPORTED_LOCATION "${BMX_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_BMX_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${BMX_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        BMX_INCLUDE_DIR
        BMX_LIBRARY
)

set(BMX_VERSION_STRING ${BMX_VERSION})
