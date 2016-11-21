#include "src/math/add.h"
#include "src/math/vector.h"
#include "src/memory/alignment.h"

#include <ctime>
#include <stdio.h>

using namespace ::Bstr::Memory;
using namespace ::Bstr::Check;
using namespace Bstr::Math;
using namespace std;

uint64_t fastDiv(uint64_t t1, uint64_t t2) {
  uint8_t powerTwo = 64 - _lzcnt_u64(t1 - 1);
}

int main() {

  printf("%llu", IS_POWER_2(-16));
  /*  size_t c = 100;
    Bstr::Math::Vector<int32_t> v;
    Bstr::Math::Vector<int32_t> v1;
    Bstr::Math::Vector<int32_t> v2;

    for (int32_t i = 0; i < c; i++) {
      v.push(i);
      v1.push(i + 1);
    }
    v2 = v * v1;

    for (int32_t i = 0; i < c; i++) {
      printf("%d ", v2[i]);
    }*/
  // v2 = v + v1;
  // v2 = std::move(v);
  /*size_t c = 20000;
  Vector<int32_t> v;
  Vector<int32_t> v1;

  int32_t *mv = new int32_t[c];
  int32_t *mv1 = new int32_t[c];

  for (int32_t i = 0; i < c; i++) {
    v.push(i);
    v1.push(i + 1);
    mv[i] = i;
    mv1[i] = i + 1;
  }

  size_t samples = 10000;

  clock_t begin = clock();
  auto v3 = v + v1;
  for (int i = 0; i < samples; i++) {
    v3 = v + v1;
  }
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", elapsed_secs);

  begin = clock();
  auto mv2 = f(mv, mv1, c);
  for (int i = 0; i < samples; i++) {
    mv2 = f(mv, mv1, c);
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", elapsed_secs);

  printf("%d %d", v3[0], mv2[0]);*/
}
