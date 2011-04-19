project(cuneiform C CXX)
cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
if(WIN32)
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
endif()

if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
   message(FATAL_ERROR "In-tree build attempt detected, aborting. Set your build dir outside your source dir, delete CMakeCache.txt from source root and try again.")
endif()

set(CF_VERSION_MAJOR "1")
set(CF_VERSION_MINOR "1")
set(CF_VERSION_PATCH "0")

set(CF_VERSION "${CF_VERSION_MAJOR}.${CF_VERSION_MINOR}.${CF_VERSION_PATCH}")
# Increment this manually whenever breaking ABI.
# http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html#AEN135
set(ABI_VERSION 0)

option(BUILD_TESTING "Enable CTest framework." OFF)

if(BUILD_TESTING)
  enable_testing()
  include(CTest)
  include(Dart)
  add_subdirectory(images)
endif()

include(install_files.cmake)

#add_subdirectory(tests)
add_subdirectory(headers)
add_subdirectory(datafiles)
add_subdirectory(cuneiform_src)

