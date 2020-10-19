find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(MXF_C_HOME $ENV{MXF_C_HOME})
message(STATUS "MXF_C home: ${MXF_C_HOME}")

# libavcodec
pkg_check_modules(PC_mxf_c QUIET mxf_c)

find_path(mxf_c_INCLUDE_DIR
        NAMES mxf/mxf.h
        PATHS ${PC_mxf_c_INCLUDE_DIRS} ${MXF_C_HOME}
        PATH_SUFFIXES include
        )

find_library(mxf_c_LIBRARY
        NAMES mxf_c
        PATHS ${PC_mxf_c_LIBRARY_DIRS} ${MXF_C_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(mxf_c
        FOUND_VAR mxf_c_FOUND
        REQUIRED_VARS
        mxf_c_LIBRARY
        mxf_c_INCLUDE_DIR
        VERSION_VAR mxf_c_VERSION
        )


if (mxf_c_FOUND AND NOT TARGET MXF::mxf_c)
    add_library(MXF::mxf_c UNKNOWN IMPORTED)
    set_target_properties(MXF::mxf_c PROPERTIES
            IMPORTED_LOCATION "${mxf_c_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_mxf_c_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${mxf_c_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        mxf_c_INCLUDE_DIR
        mxf_c_LIBRARY
)

set(mxf_c_VERSION_STRING ${mxf_c_VERSION})
