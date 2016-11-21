#ifndef BSTR_MATH_DIV
#define BSTR_MATH_DIV

#include "../check/enable.h"
#include "macro.h"
#include <emmintrin.h>
#include <immintrin.h>

namespace Bstr {
namespace Math {

// div float32 vectors(4-elements)
template <typename T, Check::EnableIfFloat32<T, int> = 0>
void div(T *const v1, T *const v2, T *const result) {
  _mm256_store_ps(result, _mm256_div_ps(CAST_GET_VAL(__m256, v1),
                                        CAST_GET_VAL(__m256, v2)));
}

// div float32 vectors(8-elements)
template <typename T, Check::EnableIfFloat64<T, int> = 0>
void div(T *const v1, T *const v2, T *const result) {
  _mm256_store_pd(result, _mm256_div_pd(CAST_GET_VAL(__m256d, v1),
                                        CAST_GET_VAL(__m256d, v2)));
}

// div two vectors(32 elements)
/*template <typename T, Check::EnableIfIntegral8<T, int> = 0>
void div(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_div_epi8(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}*/

// div two vectors(16 elements)
/*template <typename T, Check::EnableIfIntegral16<T, int> = 0>
void div(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m128i *)result,
      _mm256_div_epi16(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// div two vectors(8 elements)
template <typename T, Check::EnableIfIntegral32<T, int> = 0>
void div(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_div_epi32(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// multiplication two vectors(4 elements) with int64 type
template <typename T, Check::EnableIfIntegral64<T, int> = 0>
void div(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_div_epi64(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}
*/
}
}
#endif // BSTR_MATH_DIV
