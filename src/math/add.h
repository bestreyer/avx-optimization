#ifndef BSTR_MATH_ADD
#define BSTR_MATH_ADD

#include "../check/enable.h"
#include "macro.h"
#include <immintrin.h>

namespace Bstr {
namespace Math {

// add two vector(4 elements) with float32 type
template <typename T, Check::EnableIfFloat32<T, int> = 0>
void add(T *const v1, T *const v2, T *const result) {
  _mm256_store_ps(result, _mm256_add_ps(CAST_GET_VAL(__m256, v1),
                                        CAST_GET_VAL(__m256, v2)));
}

// add two vector(4 elements) with float64 type
template <typename T, Check::EnableIfFloat64<T, int> = 0>
void add(T *const v1, T *const v2, T *const result) {
  _mm256_store_pd(result, _mm256_add_pd(CAST_GET_VAL(__m256d, v1),
                                        CAST_GET_VAL(__m256d, v2)));
}

// add two vector(4 elements) with int8 type
template <typename T, Check::EnableIfIntegral8<T, int> = 0>
void add(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_add_epi8(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// add two vector(4 elements) with int16 type
template <typename T, Check::EnableIfIntegral16<T, int> = 0>
void add(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_add_epi16(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// add two vector(4 elements) with int32 type
template <typename T, Check::EnableIfIntegral32<T, int> = 0>
void add(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_add_epi32(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// add two vector(4 elements) with int64 type
template <typename T, Check::EnableIfIntegral64<T, int> = 0>
void add(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_add_epi64(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}
}
}
#endif // BSTR_MATH_ADD
