cmake_minimum_required(VERSION 3.10)
project(isa::utils VERSION 0.1.2)
include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")

# libisa_utils
add_library(isa_utils SHARED
  src/ArgumentList.cpp
  src/Timer.cpp
  src/utils.cpp
)
set_target_properties(isa_utils PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER "include/ArgumentList.hpp;include/Stats.hpp;include/Timer.hpp;include/utils.hpp"
)
target_include_directories(isa_utils PRIVATE include)

install(TARGETS isa_utils
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
