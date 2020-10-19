find_package(PkgConfig)
include(FindPackageHandleStandardArgs)


set(MXF_SPEC_LIB_HOME $ENV{MXF_SPEC_LIB_HOME})
message(STATUS "MXF_SPEC_LIB home: ${MXF_SPEC_LIB_HOME}")


find_path(mxf_spec_INCLUDE_DIR
        NAMES mxf_specific_parameters_lib/MxfInfo.hpp
        PATHS ${MXF_SPEC_LIB_HOME}
        PATH_SUFFIXES include
        )

find_library(mxf_spec_LIBRARY
        NAMES MxfSpecificParameters.lib
        PATHS ${MXF_SPEC_LIB_HOME}
        PATH_SUFFIXES lib
        )

find_package_handle_standard_args(mxf_spec
        FOUND_VAR mxf_spec_FOUND
        REQUIRED_VARS
        mxf_spec_LIBRARY
        mxf_spec_INCLUDE_DIR
        VERSION_VAR mxf_spec_VERSION
        )


if (mxf_spec_FOUND AND NOT TARGET MXF::mxf_spec)
    add_library(MXF::mxf_spec UNKNOWN IMPORTED)
    set_target_properties(MXF::mxf_spec PROPERTIES
            IMPORTED_LOCATION "${mxf_spec_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${mxf_spec_INCLUDE_DIR}"
            )
endif()


mark_as_advanced(
        mxf_spec_INCLUDE_DIR
        mxf_spec_LIBRARY
)

set(mxf_spec_VERSION_STRING ${mxf_spec_VERSION})
