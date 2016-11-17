#include "memory/alignment.h"
#include "memory/malloc_size.h"
#include "gtest/gtest.h"

using namespace ::Bstr::Memory;
TEST(allocate_memory, allocate_aligned_memory) {
  uint8_t n = 100;
  size_t memory_used = n * sizeof(decltype(n));

  auto ptr_sse = allocate_aligned_memory<decltype(n), Alignment::SSE>(100);
  ASSERT_TRUE(sse_aligned(ptr_sse));
  ASSERT_TRUE(malloc_size(ptr_sse) >= memory_used);

  auto ptr_avx = allocate_aligned_memory<decltype(n), Alignment::AVX>(100);
  ASSERT_TRUE(avx_aligned(ptr_avx));
  ASSERT_TRUE(malloc_size(ptr_avx) >= memory_used);

  deallocate_aligned_memory(ptr_sse);
  deallocate_aligned_memory(ptr_avx);

  ASSERT_TRUE(malloc_size(ptr_sse) == 0);
  ASSERT_TRUE(malloc_size(ptr_avx) == 0);
}
