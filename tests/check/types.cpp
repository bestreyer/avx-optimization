#include "check/types.h"
#include "gtest/gtest.h"
using namespace ::Bstr::Check;

struct NonType {};
template <bool b, template <class> class checker, typename T,
          typename T2 = NonType, typename... Args>
void CheckTypes() {
  ASSERT_TRUE(checker<T>::value == b) << __PRETTY_FUNCTION__;
  if (!std::is_same<NonType, T2>::value)
    CheckTypes<b, checker, T2, Args...>();
}

template <template <class> class checker, typename T, typename T2 = NonType,
          typename... Args>
void ValidTypes() {
  CheckTypes<true, checker, T, T2, Args...>();
}

template <template <class> class checker, typename T, typename T2 = NonType,
          typename... Args>
void InvalidTypes() {
  CheckTypes<false, checker, T, T2, Args...>();
}

TEST(Check, CheckTypes) {
  // check IsFloat32
  ValidTypes<IsFloat32, float>();
  InvalidTypes<IsFloat32, double, uint32_t, int32_t, uint64_t, int64_t>();

  // check IsFloat64
  ValidTypes<IsFloat64, double>();
  InvalidTypes<IsFloat64, float, uint32_t, int32_t, uint64_t, int64_t>();

  // check IsIntegral8
  ValidTypes<IsIntegral8, uint8_t, int8_t>();
  InvalidTypes<IsIntegral8, double, float, uint16_t, int16_t, uint32_t, int32_t,
               uint64_t, int64_t>();

  // check IsIntegral16
  ValidTypes<IsIntegral16, uint16_t, int16_t>();
  InvalidTypes<IsIntegral16, double, float, uint8_t, int8_t, uint32_t, int32_t,
               uint64_t, int64_t>();

  // check IsIntegral32
  ValidTypes<IsIntegral32, uint32_t, int32_t>();
  InvalidTypes<IsIntegral32, double, float, uint8_t, int8_t, uint16_t, int16_t,
               uint64_t, int64_t>();

  // check IsIntegral64
  ValidTypes<IsIntegral64, uint64_t, int64_t>();
  InvalidTypes<IsIntegral64, double, float, uint8_t, int8_t, uint16_t, int16_t,
               uint32_t, int32_t>();
}
