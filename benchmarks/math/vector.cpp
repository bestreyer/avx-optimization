#include "math/vector.h"
#include "benchmark/benchmark.h"

static void BM_AVXAdd(benchmark::State &state) {
  size_t count = 2000;
  Bstr::Math::Vector<uint16_t> v1(2000);
  Bstr::Math::Vector<uint16_t> v2(2000);
  Bstr::Math::Vector<uint16_t> v3(2000);
  for (int i = 0; i < count; i++) {
    v1.push(i);
    v2.push(i + 1);
  }

  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(v3 = v1 + v2);
  }
}

static void BM_DefaultAdd(benchmark::State &state) {
  size_t count = 2000;
  auto v1 = new uint16_t[count];
  auto v2 = new uint16_t[count];
  auto result = new uint16_t[count];

  for (int i = 0; i < count; i++) {
    v1[i] = i;
    v2[i] = i + 1;
  }

  while (state.KeepRunning()) {
    for (int i = 0; i < count; i++) {
      benchmark::DoNotOptimize(result[i] = v1[i] + v2[i]);
    }
  }
}

static void BM_AVXMultiple(benchmark::State &state) {
  size_t count = 2000;
  Bstr::Math::Vector<int8_t> v1(2000);
  Bstr::Math::Vector<int8_t> v2(2000);
  Bstr::Math::Vector<int8_t> v3(2000);
  for (int i = 0; i < count; i++) {
    v1.push(i);
    v2.push(i + 1);
  }

  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(v3 = v1 * v2);
  }
}

static void BM_DefaultMultiple(benchmark::State &state) {
  size_t count = 2000;
  auto v1 = new uint32_t[count];
  auto v2 = new uint32_t[count];
  auto result = new uint32_t[count];

  for (int i = 0; i < count; i++) {
    v1[i] = i;
    v2[i] = i + 1;
  }

  while (state.KeepRunning()) {
    for (int i = 0; i < count; i++) {
      benchmark::DoNotOptimize(result[i] = v1[i] + v2[i]);
    }
  }
}

BENCHMARK(BM_AVXAdd);
BENCHMARK(BM_DefaultAdd);
BENCHMARK(BM_AVXMultiple);
BENCHMARK(BM_DefaultMultiple);

BENCHMARK_MAIN();
