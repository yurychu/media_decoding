cmake_minimum_required(VERSION 3.15)
project(master_server_proj)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.72.0 COMPONENTS program_options REQUIRED)

add_executable(
        master_server
        master_server/master_server.cpp
        master_server/include/master_server/MasterServer.hpp
        master_server/src/MasterServer.cpp
)

target_compile_definitions(
        master_server
        PRIVATE
        #        BOOST_LOG_ENABLE_WARNINGS
        #        BOOST_THREAD_DYN_LINK
        #        BOOST_LOG_DYN_LINK
        BOOST_ALL_DYN_LINK
)

if (WIN32)
    target_compile_definitions(
            master_server
            PRIVATE
            _WIN32_WINNT=0x0A00  # windows 10 only
    )
endif()

target_include_directories(
        master_server
        PRIVATE
        master_server/include
)

target_link_directories(
        master_server
        PRIVATE
        ${Boost_LIBRARY_DIRS}
)

target_link_libraries(
        master_server
        PRIVATE
        Boost::program_options
)
