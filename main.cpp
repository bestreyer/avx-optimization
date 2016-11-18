#include "src/math/add.h"
#include "src/math/vector.h"
#include "src/memory/alignment.h"
#include <ctime>
#include <stdio.h>

using namespace ::Bstr::Memory;
using namespace ::Bstr::Check;
using namespace Bstr::Math;
using namespace std;

/*int32_t *f(int32_t *v1, int32_t *v2, size_t len) {
  int32_t *result = new int32_t[len];
  for (int i = 0; i < len; i++) {
    result[i] = v1[i] + v2[i];
  }

  return result;
}*/

int main() {
  size_t c = 20000;
  Bstr::Math::Vector<int32_t> v;
  Bstr::Math::Vector<int32_t> v1;
  Bstr::Math::Vector<int32_t> v2;

  for (int32_t i = 0; i < c; i++) {
    v.push(i);
    v1.push(i + 1);
  }
  v.push(20);
  v2 = v + v1;
  v2 = std::move(v);
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
