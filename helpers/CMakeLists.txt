cmake_minimum_required(VERSION 3.10.2)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/helpers.cmake)

# {target_{PROJECT_NAME}} variables needed for 'find_module' find target_{PROJECT_NAME}
set(utils_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils PARENT_SCOPE)

add_subdirectory(utils)
