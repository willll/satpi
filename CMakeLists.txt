cmake_minimum_required(VERSION 3.14)
project(dreampi_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress FindBoost warning for CMake 3.28+
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

# Set directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

include_directories(${INC_DIR})

# Collect source files
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in ${SRC_DIR}")
endif()

# Create the executable
add_executable(dreampi_cpp ${SOURCES})

if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling: using manual Boost linking")
    include_directories(/usr/arm-linux-gnueabihf/include)
    link_directories(/usr/arm-linux-gnueabihf/lib)
    target_link_libraries(dreampi_cpp
        boost_log
        boost_log_setup
        boost_system
        boost_thread
        pthread
    )
else()
    set(BOOST_COMPONENTS log log_setup system thread)
    find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
    if(TARGET Boost::log)
        message(STATUS "Using Boost::log config-based linking")
        target_link_libraries(dreampi_cpp
            Boost::log
            Boost::log_setup
            Boost::system
            Boost::thread
            pthread
        )
    else()
        message(FATAL_ERROR "Modern Boost CMake targets not found. Please use a recent Boost version with CMake config files.")
    endif()
endif()
