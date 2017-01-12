#ifndef BSTR_MATH_MULTIPLICATION
#define BSTR_MATH_MULTIPLICATION

#include "../check/enable.h"
#include "macro.h"
#include <emmintrin.h>
#include <immintrin.h>

namespace Bstr {
namespace Math {

__m128i mullo_epi8(__m128i a, __m128i b) {
  __m128i dst_even = _mm_mullo_epi16(a, b);
  __m128i dst_odd = _mm_mullo_epi16(_mm_srli_epi16(a, 8), _mm_srli_epi16(b, 8));

  return _mm_or_si128(_mm_slli_epi16(dst_odd, 8),
                      _mm_and_si128(dst_even, _mm_set1_epi16(0xFF)));
}

// Multiplies float32 vectors(4-elements)
template <typename T, Check::EnableIfFloat32<T, int> = 0>
void multiplication(T *const v1, T *const v2, T *const result) {
  _mm256_store_ps(result, _mm256_mul_ps(CAST_GET_VAL(__m256, v1),
                                        CAST_GET_VAL(__m256, v2)));
}

// Multiplies float32 vectors(8-elements)
template <typename T, Check::EnableIfFloat64<T, int> = 0>
void multiplication(T *const v1, T *const v2, T *const result) {
  _mm256_store_pd(result, _mm256_mul_pd(CAST_GET_VAL(__m256d, v1),
                                        CAST_GET_VAL(__m256d, v2)));
}

// multiplication two vectors(32 elements)
template <typename T, Check::EnableIfIntegral8<T, int> = 0>
void multiplication(T *const v1, T *const v2, T *const result) {
  constexpr size_t align = 16;
  _mm_store_si128(
      reinterpret_cast<__m128i *>(result),
      mullo_epi8(CAST_GET_VAL(__m128i, v1), CAST_GET_VAL(__m128i, v2)));
  _mm_store_si128((__m128i *)(result + align),
                  mullo_epi8(CAST_GET_VAL(__m128i, v1 + align),
                             CAST_GET_VAL(__m128i, v2 + align)));
}

// multiplication two vectors(16 elements)
template <typename T, Check::EnableIfIntegral16<T, int> = 0>
void multiplication(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_mullo_epi16(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// multiplication two vectors(8 elements)
template <typename T, Check::EnableIfIntegral32<T, int> = 0>
void multiplication(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_mullo_epi32(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}

// multiplication two vectors(4 elements) with int64 type
/*template <typename T, Check::EnableIfIntegral64<T, int> = 0>
void multiplication(T *const v1, T *const v2, T *const result) {
  _mm256_store_si256(
      (__m256i *)result,
      _mm256_mullo_epi64(CAST_GET_VAL(__m256i, v1), CAST_GET_VAL(__m256i, v2)));
}*/
}
}
#endif // BSTR_MATH_MULTIPLICATION
