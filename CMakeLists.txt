cmake_minimum_required(VERSION 3.8)
project(isa::utils VERSION 1.0)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")

# libisa_utils
set(LIBRARY_SOURCE
  src/ArgumentList.cpp
  src/Timer.cpp
  src/utils.cpp
)
set(LIBRARY_HEADER
  include/ArgumentList.hpp
  include/Statistics.hpp
  include/Timer.hpp
  include/utils.hpp
)
add_library(isa_utils SHARED ${LIBRARY_SOURCE} ${LIBRARY_HEADER})
set_target_properties(isa_utils PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER "include/ArgumentList.hpp;include/Statistics.hpp;include/Timer.hpp;include/utils.hpp"
)
target_include_directories(isa_utils PRIVATE include)

install(TARGETS isa_utils
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Unit testing
enable_testing()
set(TEST_LINK_LIBRARIES gtest gtest_main pthread)
## utilsTest
add_executable(utilsTest
  test/utilsTest.cpp
)
target_include_directories(utilsTest PRIVATE include)
target_link_libraries(utilsTest PRIVATE isa_utils ${TEST_LINK_LIBRARIES})
add_test(NAME utilsTest COMMAND utilsTest)
