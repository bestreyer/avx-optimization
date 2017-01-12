MESSAGE("BUILD WITH TESTS")

# create tests folder
set(TEST_OUTPUT_FOLDER ${BIN_FOLDER}/tests)
set(PROJECT_TEST_NAME ${PROJECT_NAME}-test)
file(MAKE_DIRECTORY ${TEST_OUTPUT_FOLDER})

# path to google lib folder
set(GOOGLE_TEST_LIB ${PROJECT_SOURCE_DIR}/lib/gtest)
#build googletest
SET_OPTION(BUILD_GTEST ON)
add_subdirectory(${GOOGLE_TEST_LIB})
enable_testing()
file(GLOB_RECURSE TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)

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
