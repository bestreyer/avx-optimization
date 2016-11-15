#include <stdint.h>
#include <stdlib.h>
#include <immintrin.h>
#include <stdio.h>
#include <iostream>
#include "src/memory/aligment.h"

using namespace ::Bstr::Memory;

int main() {
  auto ptr = avx_allocate_aligned_memory<uint16_t>(16);
  auto ptr1 = sse_allocate_aligned_memory<uint16_t>(16);
  deallocate_aligned_memory(ptr);
  deallocate_aligned_memory(ptr1);
}
