cmake_minimum_required(VERSION 3.10.2)

project(
    shape
    LANGUAGES CXX
    VERSION 1.0.0
)

find_package(utils REQUIRED)

set(_INC_FOLDER_NAME include)
set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}/${PROJECT_NAME})
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
   
add_executable(
    ${PROJECT_NAME}
        ${_INC_DIR}/ShapeApplication.h
        ${_INC_DIR}/config/ShapeConfig.h
        ${_INC_DIR}/config/ShapeConfigLoader.h
        ${_INC_DIR}/geometry/BatmanGeometry.h
        ${_INC_DIR}/geometry/config/BatmanShapeConfig.h
        ${_INC_DIR}/helpers/BatmanTaskDispatcher.h
        
     
        ${_SRC_DIR}/main.cpp
        ${_SRC_DIR}/ShapeApplication.cpp
        ${_SRC_DIR}/config/ShapeConfigLoader.cpp
        ${_SRC_DIR}/geometry/BatmanGeometry.cpp
        ${_SRC_DIR}/helpers/BatmanTaskDispatcher.cpp
)

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}>
        $<INSTALL_INTERFACE:${_INC_FOLDER_NAME}>
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE
        utils::utils
)

set_target_cpp_standard(${PROJECT_NAME} 20)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})
#enable_target_sanitizer(${PROJECT_NAME} "address")

    