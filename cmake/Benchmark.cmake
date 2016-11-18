MESSAGE("Build with benchmarks")

set(GOOGLE_BENCHMARK_DIR ${PROJECT_SOURCE_DIR}/lib/benchmark)
set(BENCHMARK_OUTPUT_FOLDER ${BIN_FOLDER}/benchmarks)

file(MAKE_DIRECTORY ${BENCHMARK_OUTPUT_FOLDER})

SET_OPTION(BENCHMARK_ENABLE_TESTING OFF)
SET_OPTION(CMAKE_BUILD_TYPE "Release")
SET_OPTION(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BENCHMARK_OUTPUT_FOLDER})

add_subdirectory(${GOOGLE_BENCHMARK_DIR})
file(GLOB_RECURSE ALL_BENCH_CPP ${PROJECT_SOURCE_DIR}/benchmarks/*.cpp)
foreach(ONE_BENCH_CPP ${ALL_BENCH_CPP})
  get_filename_component(ONE_BENCH_EXEC ${ONE_BENCH_CPP} NAME_WE)
  set(TARGET_NAME ${ONE_BENCH_EXEC}_benchmark)
  add_executable(${TARGET_NAME} ${ONE_BENCH_CPP})
  add_dependencies(${TARGET_NAME} benchmark)
  target_link_libraries(
    ${TARGET_NAME}
    benchmark
  )
endforeach()
