include(CMakeFindDependencyMacro)

if(NOT TARGET utils::utils)
  include(${CMAKE_CURRENT_LIST_DIR}/utilsTargets.cmake)
endif()
