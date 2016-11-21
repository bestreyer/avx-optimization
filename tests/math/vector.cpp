#include "math/vector.h"
#include "gtest/gtest.h"
#include <limits>
#include <random>

namespace math = ::Bstr::Math;

template <typename T> T checkAdd(T &v1, T &v2) { return v1 + v2; }
template <typename T> T checkSub(T &v1, T &v2) { return v1 - v2; }
template <typename T> T checkMul(T &v1, T &v2) { return v1 * v2; }

template <typename T>
void checkOperator(math::Vector<T> (math::Vector<T>::*func)(math::Vector<T> &),
                   T (*checker)(T &, T &)) {
  constexpr size_t els = 2000;
  auto min = std::numeric_limits<T>::min();
  auto max = std::numeric_limits<T>::max();

  auto mind2 = min / 2;
  auto maxd2 = max / 2;

  math::Vector<T> v1(els);
  math::Vector<T> v2(els);

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<T> distribution((T)mind2, (T)maxd2);

  for (size_t i = 0; i < els; i++) {
    if (std::is_floating_point<T>::value == true) {
      v1.push((T)(distribution(gen) + distribution(gen)) / distribution(gen));
      v2.push((T)(distribution(gen) + distribution(gen)) / distribution(gen));
    } else {
      v1.push(distribution(gen));
      v2.push(distribution(gen));
    }
  }

  auto v3 = (v1.*func)(v2);
  for (size_t i = 0; i < els; i++) {
    ASSERT_EQ(v3[i], (T)(checker(v1[i], v2[i])));
  }
}

#define CHECK_OPERATION(type, op, checker)                                     \
  auto checker##_##type = &math::Vector<type>::operator op;                    \
  checkOperator<type>(checker##_##type, &checker)

#define CHECK_ADD(type) CHECK_OPERATION(type, +, checkAdd)
#define CHECK_SUB(type) CHECK_OPERATION(type, -, checkSub)
#define CHECK_MUL(type) CHECK_OPERATION(type, *, checkMul)

TEST(Math, VectorAdd) {
  CHECK_ADD(float);
  CHECK_ADD(double);

  CHECK_ADD(int8_t);
  CHECK_ADD(uint8_t);

  CHECK_ADD(int16_t);
  CHECK_ADD(uint16_t);

  CHECK_ADD(int32_t);
  CHECK_ADD(uint32_t);

  CHECK_ADD(int64_t);
  CHECK_ADD(uint64_t);
}

TEST(Math, VectorSub) {
  CHECK_SUB(float);
  CHECK_SUB(double);

  CHECK_SUB(int8_t);
  CHECK_SUB(uint8_t);

  CHECK_SUB(int16_t);
  CHECK_SUB(uint16_t);

  CHECK_SUB(int32_t);
  CHECK_SUB(uint32_t);

  CHECK_SUB(int64_t);
  CHECK_SUB(uint64_t);
}

TEST(Math, VectorMul) {
  CHECK_MUL(float);
  CHECK_MUL(double);

  CHECK_MUL(int8_t);
  CHECK_MUL(uint8_t);

  CHECK_MUL(int16_t);
  CHECK_MUL(uint16_t);

  CHECK_MUL(int32_t);
  CHECK_MUL(uint32_t);

  /*CHECK_MUL(int64_t);
  CHECK_MUL(uint64_t);*/

  /*CHECK_SUB(int64_t);
  CHECK_SUB(uint64_t);*/
}
