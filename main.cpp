#include "src/memory/alignment.h"
#include <immintrin.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

using namespace ::Bstr::Memory;

int main() {
  auto ptr = allocate_aligned_memory<uint16_t, Alignment::AVX>(16);
  printf("%d\n", sse_aligned(ptr));
  for (int i = 0; i < 16; i++) {
    ptr[i] = i;
  }

  auto ptr1 = reallocate_aligned_memory<uint16_t, Alignment::AVX>(ptr, 32);

  for (int i = 0; i < 16; i++) {
    printf("%d ", ptr1[i]);
  }

  // deallocate_aligned_memory(ptr);
}
