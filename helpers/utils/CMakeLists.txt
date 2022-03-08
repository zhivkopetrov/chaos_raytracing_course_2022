#author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(
    utils 
    LANGUAGES CXX
    VERSION 1.0.0
)

find_package(Threads REQUIRED)

set(_INC_FOLDER_NAME include)
set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}/${PROJECT_NAME})
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME}
    STATIC
        ${_INC_DIR}/class/NonCopyable.h
        ${_INC_DIR}/class/NonMoveable.h
        ${_INC_DIR}/concurrency/ThreadSafeQueue.h
        ${_INC_DIR}/data_type/EnumClassUtils.h
        ${_INC_DIR}/data_type/FloatingPoint.h
        ${_INC_DIR}/file/PpmFileWritter.h
        ${_INC_DIR}/file/IniFileParser.h
        ${_INC_DIR}/geometry/Point2f.h
        ${_INC_DIR}/rendering/color/Color24.h
        ${_INC_DIR}/rendering/color/Color32.h
        ${_INC_DIR}/time/Time.h
        ${_INC_DIR}/log/Log.h
        ${_INC_DIR}/ErrorCode.h
        
        ${_SRC_DIR}/file/PpmFileWritter.cpp
        ${_SRC_DIR}/file/IniFileParser.cpp
        ${_SRC_DIR}/geometry/Point2f.cpp
        ${_SRC_DIR}/rendering/color/Color24.cpp
        ${_SRC_DIR}/rendering/color/Color32.cpp
        ${_SRC_DIR}/time/Time.cpp
        ${_SRC_DIR}/log/Log.cpp
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}>
        $<INSTALL_INTERFACE:${_INC_FOLDER_NAME}>
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        Threads::Threads
)

set_target_cpp_standard(${PROJECT_NAME} 20)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})

