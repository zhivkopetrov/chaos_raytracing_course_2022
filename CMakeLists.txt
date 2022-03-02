cmake_minimum_required(VERSION 3.10.2)

project(
    raytracing
    LANGUAGES CXX
    VERSION 1.0.0
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(DEFAULT_BUILD_TYPE Debug)
        message(STATUS 
            "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
        
        set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
            STRING "Choose the type of build." FORCE)
endif()

# static helper libraries
add_subdirectory(helpers)

# executables
add_subdirectory(tasks)
