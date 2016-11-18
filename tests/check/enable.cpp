#include "check/enable.h"
#include "gtest/gtest.h"
using namespace ::Bstr::Check;

enum TypeEnum { Float32, Float64, Int8, Int16, Int32, Int64 };
template <typename T, EnableIfFloat32<T, int> = 0> TypeEnum test() {
  return TypeEnum::Float32;
}

template <typename T, EnableIfFloat64<T, int> = 0> TypeEnum test() {
  return TypeEnum::Float64;
}

template <typename T, EnableIfIntegral8<T, int> = 0> TypeEnum test() {
  return TypeEnum::Int8;
}

template <typename T, EnableIfIntegral16<T, int> = 0> TypeEnum test() {
  return TypeEnum::Int16;
}

template <typename T, EnableIfIntegral32<T, int> = 0> TypeEnum test() {
  return TypeEnum::Int32;
}

template <typename T, EnableIfIntegral64<T, int> = 0> TypeEnum test() {
  return TypeEnum::Int64;
}

TEST(Check, CheckEnable) {
  ASSERT_EQ(test<float>(), TypeEnum::Float32);
  ASSERT_EQ(test<double>(), TypeEnum::Float64);
  ASSERT_EQ(test<int8_t>(), TypeEnum::Int8);
  ASSERT_EQ(test<int16_t>(), TypeEnum::Int16);
  ASSERT_EQ(test<int32_t>(), TypeEnum::Int32);
  ASSERT_EQ(test<int64_t>(), TypeEnum::Int64);
}
