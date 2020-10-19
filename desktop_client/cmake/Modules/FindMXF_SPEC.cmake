find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(MXF_SPEC_LIB_HOME $ENV{MXF_SPEC_LIB_HOME})
message(STATUS "MXF_SPEC_LIB home: ${MXF_SPEC_LIB_HOME}")


find_path(MXF_SPEC_INCLUDE_DIR
        NAMES mxf_specific_parameters_lib/MxfInfo.hpp
        PATHS ${MXF_SPEC_LIB_HOME}
        PATH_SUFFIXES include
        )

find_library(MXF_SPEC_LIBRARY
        NAMES MxfSpecificParameters.lib
        PATHS ${MXF_SPEC_LIB_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(MXF_SPEC
        FOUND_VAR MXF_SPEC_FOUND
        REQUIRED_VARS
        MXF_SPEC_LIBRARY
        MXF_SPEC_INCLUDE_DIR
        VERSION_VAR MXF_SPEC_VERSION
        )


if (MXF_SPEC_FOUND AND NOT TARGET MXF::mxf_spec)
    add_library(MXF::mxf_spec UNKNOWN IMPORTED)
    set_target_properties(MXF::mxf_spec PROPERTIES
            IMPORTED_LOCATION "${MXF_SPEC_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${MXF_SPEC_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        MXF_SPEC_INCLUDE_DIR
        MXF_SPEC_LIBRARY
)

set(MXF_SPEC_VERSION_STRING ${MXF_SPEC_VERSION})
