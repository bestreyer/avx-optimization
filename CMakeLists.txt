cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "avx-optimization")
project(${PROJECT_NAME})

option(test "Build tests" OFF)

set(SRC_FOLDER ${PROJECT_SOURCE_DIR}/src)
set(BIN_FOLDER ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${BIN_FOLDER})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_FOLDER})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_executable(${PROJECT_NAME} main.cpp)

if (tests)
  MESSAGE("BUILD TESTS")

  # create tests folder
  set(TEST_OUTPUT_FOLDER ${BIN_FOLDER}/tests)
  set(PROJECT_TEST_NAME ${PROJECT_NAME}-test)
  file(MAKE_DIRECTORY ${TEST_OUTPUT_FOLDER})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_FOLDER})

  add_subdirectory(${PROJECT_SOURCE_DIR}/lib/gtest)
  enable_testing()
  file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

  include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
  )

  add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
  target_link_libraries(${PROJECT_TEST_NAME}
        ${gtest_SOURCE_DIR}/libgtest.a
        ${gtest_SOURCE_DIR}/libgtest_main.a
  )

  add_test(test ${TEST_OUTPUT_FOLDER}/${PROJECT_TEST_NAME})

endif()
