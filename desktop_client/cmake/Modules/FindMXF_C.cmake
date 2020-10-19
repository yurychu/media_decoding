find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(MXF_C_HOME $ENV{MXF_C_HOME})
message(STATUS "MXF_C home: ${MXF_C_HOME}")

# libavcodec
pkg_check_modules(PC_MXF_C QUIET MXF_C)

find_path(MXF_C_INCLUDE_DIR
        NAMES mxf/mxf.h
        PATHS ${PC_MXF_C_INCLUDE_DIRS} ${MXF_C_HOME}
        PATH_SUFFIXES include
        )

find_library(MXF_C_LIBRARY
        NAMES mxf_c
        PATHS ${PC_MXF_C_LIBRARY_DIRS} ${MXF_C_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(MXF_C
        FOUND_VAR MXF_C_FOUND
        REQUIRED_VARS
        MXF_C_LIBRARY
        MXF_C_INCLUDE_DIR
        VERSION_VAR MXF_C_VERSION
        )


if (MXF_C_FOUND AND NOT TARGET MXF::mxf_c)
    add_library(MXF::mxf_c UNKNOWN IMPORTED)
    set_target_properties(MXF::mxf_c PROPERTIES
            IMPORTED_LOCATION "${MXF_C_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_MXF_C_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${MXF_C_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        MXF_C_INCLUDE_DIR
        MXF_C_LIBRARY
)

set(MXF_C_VERSION_STRING ${MXF_C_VERSION})
