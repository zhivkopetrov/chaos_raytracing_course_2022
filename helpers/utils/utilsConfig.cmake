include(CMakeFindDependencyMacro)

#find_dependency will correctly forward REQUIRED or QUIET args to the consumer
#find_package is only for internal use
find_dependency(Threads REQUIRED)

if(NOT TARGET utils::utils)
  include(${CMAKE_CURRENT_LIST_DIR}/utilsTargets.cmake)
endif()
