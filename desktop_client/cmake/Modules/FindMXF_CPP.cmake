find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(MXF_CPP_HOME $ENV{MXF_CPP_HOME})
message(STATUS "MXF_CPP home: ${MXF_CPP_HOME}")


pkg_check_modules(PC_MXF_CPP QUIET MXF_CPP)

find_path(MXF_CPP_INCLUDE_DIR
        NAMES libMXF++/MXF.h
        PATHS ${PC_MXF_CPP_INCLUDE_DIRS} ${MXF_CPP_HOME}
        PATH_SUFFIXES include
        )

find_library(MXF_CPP_LIBRARY
        NAMES mxf_cpp
        PATHS ${PC_MXF_CPP_LIBRARY_DIRS} ${MXF_CPP_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(MXF_CPP
        FOUND_VAR MXF_CPP_FOUND
        REQUIRED_VARS
        MXF_CPP_LIBRARY
        MXF_CPP_INCLUDE_DIR
        VERSION_VAR MXF_CPP_VERSION
        )


if (MXF_CPP_FOUND AND NOT TARGET MXF::mxf_cpp)
    add_library(MXF::mxf_cpp UNKNOWN IMPORTED)
    set_target_properties(MXF::mxf_cpp PROPERTIES
            IMPORTED_LOCATION "${MXF_CPP_LIBRARY}"
            INTERFACE_COMPILE_OPTIONS "${PC_MXF_CPP_CFLAGS_OTHER}"
            INTERFACE_INCLUDE_DIRECTORIES "${MXF_CPP_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        MXF_CPP_INCLUDE_DIR
        MXF_CPP_LIBRARY
)

set(MXF_CPP_VERSION_STRING ${MXF_CPP_VERSION})
