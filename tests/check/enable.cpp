#include "check/enable.h"
#include "gtest/gtest.h"
using namespace ::Bstr::Check;

template <typename T, template <typename, typename> class EnableType>
struct CheckEnable {
private:
  struct general {};
  struct special : general {};
  template <typename Q> static EnableType<Q, uint8_t> enableCheck(special);
  template <typename Q> static uint16_t enableCheck(general);

public:
  static constexpr bool value =
      (sizeof(enableCheck<T>(special())) == sizeof(uint8_t));
};

struct NonType {};

template <template <typename, typename> class EnableType, typename T1,
          typename T2 = NonType, typename... Args>
void check(bool f) {
  constexpr bool a = CheckEnable<T1, EnableType>::value;
  ASSERT_EQ(a, f) << __PRETTY_FUNCTION__;
  if (!std::is_same<T2, NonType>::value)
    check<EnableType, T2, Args...>(f);
}

template <template <typename, typename> class EnableType, typename T1,
          typename T2 = NonType, typename... Args>
void enable() {
  check<EnableType, T1, T2, Args...>(true);
}

template <template <typename, typename> class EnableType, typename T1,
          typename T2 = NonType, typename... Args>
void disable() {
  check<EnableType, T1, T2, Args...>(false);
}

TEST(Check, CheckEnable) {
  enable<EnableIfFloat32, float>();
  disable<EnableIfFloat32, double, int8_t, uint8_t, int16_t, uint16_t, int32_t,
          uint32_t, int64_t, uint64_t>();

  enable<EnableIfFloat64, double>();
  disable<EnableIfFloat64, float, int8_t, uint8_t, int16_t, uint16_t, int32_t,
          uint32_t, int64_t, uint64_t>();

  enable<EnableIfIntegral8, int8_t, uint8_t>();
  disable<EnableIfIntegral8, float, double, int16_t, uint16_t, int32_t,
          uint32_t, int64_t, uint64_t>();

  enable<EnableIfIntegral16, int16_t, uint16_t>();
  disable<EnableIfIntegral16, float, double, int8_t, uint8_t, int32_t, uint32_t,
          int64_t, uint64_t>();

  enable<EnableIfIntegral32, int32_t, uint32_t>();
  disable<EnableIfIntegral32, float, double, int16_t, uint16_t, int8_t, uint8_t,
          int64_t, uint64_t>();

  enable<EnableIfIntegral64, int64_t, uint64_t>();
  disable<EnableIfIntegral64, float, double, int16_t, uint16_t, int8_t, uint8_t,
          int32_t, uint32_t>();

  enable<EnableIfUIntegral8, uint8_t>();
  disable<EnableIfUIntegral8, float, double, int16_t, uint16_t, int32_t,
          uint32_t, int64_t, uint64_t, int8_t>();

  enable<EnableIfSIntegral8, int8_t>();
  disable<EnableIfSIntegral8, float, double, int16_t, uint16_t, int32_t,
          uint32_t, int64_t, uint64_t, uint8_t>();

  enable<EnableIfUIntegral16, uint16_t>();
  disable<EnableIfUIntegral16, float, double, int8_t, uint8_t, int32_t,
          uint32_t, int64_t, uint64_t, int16_t>();

  enable<EnableIfSIntegral16, int16_t>();
  disable<EnableIfSIntegral16, float, double, int8_t, uint8_t, int32_t,
          uint32_t, int64_t, uint64_t, uint16_t>();

  enable<EnableIfUIntegral32, uint32_t>();
  disable<EnableIfUIntegral32, float, double, int16_t, uint16_t, int8_t,
          uint8_t, int64_t, uint64_t, int32_t>();

  enable<EnableIfSIntegral32, int32_t>();
  disable<EnableIfSIntegral32, float, double, int16_t, uint16_t, int8_t,
          uint8_t, int64_t, uint64_t, uint32_t>();

  enable<EnableIfUIntegral64, uint64_t>();
  disable<EnableIfUIntegral64, float, double, int16_t, uint16_t, int8_t,
          uint8_t, int32_t, uint32_t, int64_t>();

  enable<EnableIfSIntegral64, int64_t>();
  disable<EnableIfSIntegral64, float, double, int16_t, uint16_t, int8_t,
          uint8_t, int32_t, uint32_t, uint64_t>();
}
