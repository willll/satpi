cmake_minimum_required(VERSION 3.14)
project(dreampi_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Boost: Prefer config-based linking, fallback to FindBoost
set(BOOST_COMPONENTS log log_setup system thread)

# First try config-based linking (modern)
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
    # Fallback for older Boost versions on Raspberry Pi
    message(WARNING "Falling back to legacy FindBoost method")
    find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    # If legacy Boost found, link manually
    target_link_libraries(dreampi_cpp
        ${Boost_LOG_LIBRARY}
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        pthread
    )
endif()
