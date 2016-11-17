#include "memory/alignment.h"
#include "memory/malloc_size.h"
#include "gtest/gtest.h"

using namespace ::Bstr::Memory;
TEST(allocate_memory, allocate_aligned_memory) {
  typedef uint8_t tt;
  tt n = 100;
  tt rn = 200;
  size_t memory_used = n * sizeof(tt);

  // check allocate
  auto ptr_sse = allocate_aligned_memory<tt, Alignment::SSE>(n);
  auto ptr_avx = allocate_aligned_memory<tt, Alignment::AVX>(n);

  // check align
  ASSERT_TRUE(sse_aligned(ptr_sse));
  ASSERT_TRUE(avx_aligned(ptr_avx));

  // check size
  ASSERT_TRUE(malloc_size(ptr_sse) >= memory_used);
  ASSERT_TRUE(malloc_size(ptr_avx) >= memory_used);

  // check reallocate
  auto ptr_sse_to_avx =
      reallocate_aligned_memory<tt, Alignment::AVX>(ptr_sse, rn);
  auto ptr_avx_to_sse =
      reallocate_aligned_memory<tt, Alignment::SSE>(ptr_avx, rn);

  ASSERT_TRUE(sse_aligned(ptr_avx_to_sse));
  ASSERT_TRUE(avx_aligned(ptr_sse_to_avx));

  deallocate_aligned_memory(ptr_sse_to_avx);
  deallocate_aligned_memory(ptr_avx_to_sse);

  // check that all pointer is null size
  ASSERT_TRUE(malloc_size(ptr_sse) == 0);
  ASSERT_TRUE(malloc_size(ptr_avx) == 0);
  ASSERT_TRUE(malloc_size(ptr_sse_to_avx) == 0);
  ASSERT_TRUE(malloc_size(ptr_avx_to_sse) == 0);
}
