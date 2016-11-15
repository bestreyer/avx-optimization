project(avx-optimization)
# include_directories("src")

cmake_minimum_required(VERSION 3.0)

set(SRC_FOLDER src)
set(BIN_FOLDER bin)
file(MAKE_DIRECTORY ${BIN_FOLDER})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_FOLDER})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(SRC_LIST
  ${SRC_FOLDER}/RandomPrimaryGenerator.cpp
  ${SRC_FOLDER}/BloomFilter.cpp
  ${SRC_FOLDER}/LRUCache.cpp
  ${SRC_FOLDER}/main.cpp
)

add_executable(${PROJECT_NAME} main.cpp)
