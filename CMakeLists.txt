cmake_minimum_required(VERSION 3.10)
project(isa::utils VERSION 1.0)
include(GNUInstallDirs)

add_library(isa_utils SHARED
  src/ArgumentList.cpp
  src/Timer.cpp
  src/utils.cpp
)
set_target_properties(isa_utils PROPERTIES 
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER include/ArgumentList.hpp include/Statistics.hpp include/Timer.hpp include/utils.hpp
)
target_include_directories(isa_utils PRIVATE include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -march=native -mtune=native")

install(TARGETS isa_utils
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
