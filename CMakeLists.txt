cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "avx-optimization")
project(${PROJECT_NAME})

macro(SET_OPTION option value)
  set(${option} ${value} CACHE "" INTERNAL FORCE)
endmacro()

option(test "Build tests" OFF)

set(SRC_FOLDER ${PROJECT_SOURCE_DIR}/src)
set(BIN_FOLDER ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${BIN_FOLDER})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_FOLDER})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_executable(${PROJECT_NAME} main.cpp)

if (test)

  MESSAGE("BUILD WITH TESTS")

  # create tests folder
  set(TEST_OUTPUT_FOLDER ${BIN_FOLDER}/tests)
  set(PROJECT_TEST_NAME ${PROJECT_NAME}-test)
  file(MAKE_DIRECTORY ${TEST_OUTPUT_FOLDER})

  set(GOOGLE_TEST_LIB ${PROJECT_SOURCE_DIR}/lib/gtest)
  #build googletest
  SET_OPTION(BUILD_GTEST ON)
  add_subdirectory(${GOOGLE_TEST_LIB})

  enable_testing()
  file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

  include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
  )

  SET_OPTION(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_FOLDER})
  add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
  add_dependencies(${PROJECT_TEST_NAME} gtest_main)

  target_link_libraries(
        ${PROJECT_TEST_NAME}
        ${gtest_BINARY_DIR}/libgtest.a
        ${gtest_BINARY_DIR}/libgtest_main.a
  )

  add_test(test ${TEST_OUTPUT_FOLDER}/${PROJECT_TEST_NAME})
else()
  MESSAGE("BUILD WITHOUT TESTS")
endif()
