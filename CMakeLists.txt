cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "avx-optimization")
project(${PROJECT_NAME})

macro(SET_OPTION option value)
  set(${option} ${value} CACHE "" INTERNAL FORCE)
endmacro()

option(test "Build tests" OFF)
option(benchmark "Build benchmarks" OFF)

set(SRC_FOLDER ${PROJECT_SOURCE_DIR}/src)
set(BIN_FOLDER ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${BIN_FOLDER})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_FOLDER})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -mavx2 -mlzcnt -O3")

add_executable(${PROJECT_NAME} main.cpp)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if (test)
  include(Test)
endif()

if (benchmark)
  include(Benchmark)
endif()
