find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(MXF_CPP_HOME $ENV{MXF_CPP_HOME})
message(STATUS "MXF_CPP home: ${MXF_CPP_HOME}")

# libavcodec
pkg_check_modules(PC_mxf_cpp QUIET mxf_cpp)

find_path(mxf_cpp_INCLUDE_DIR
        NAMES libMXF++/MXF.h
        PATHS ${PC_mxf_cpp_INCLUDE_DIRS} ${MXF_CPP_HOME}
        PATH_SUFFIXES include
        )

find_library(mxf_cpp_LIBRARY
        NAMES mxf_cpp
        PATHS ${PC_mxf_cpp_LIBRARY_DIRS} ${MXF_CPP_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(mxf_cpp
        FOUND_VAR mxf_cpp_FOUND
        REQUIRED_VARS
        mxf_cpp_LIBRARY
        mxf_cpp_INCLUDE_DIR
        VERSION_VAR mxf_cpp_VERSION
        )


if (mxf_cpp_FOUND AND NOT TARGET MXF::mxf_cpp)
    add_library(MXF::mxf_cpp UNKNOWN IMPORTED)
    set_target_properties(MXF::mxf_cpp PROPERTIES
            IMPORTED_LOCATION "${mxf_cpp_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_mxf_cpp_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${mxf_cpp_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        mxf_cpp_INCLUDE_DIR
        mxf_cpp_LIBRARY
)

set(mxf_cpp_VERSION_STRING ${mxf_cpp_VERSION})
