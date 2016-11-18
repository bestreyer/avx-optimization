#include "memory/alignment.h"
#include "memory/malloc_size.h"
#include "gtest/gtest.h"

using namespace ::Bstr::Memory;
TEST(AllocateMemory, AllocateAlignedMemory) {
  typedef uint8_t tt;
  tt n = 100;
  tt rn = 200;
  size_t memory_used = n * sizeof(tt);

  // check allocate
  auto ptr_sse = AllocateAlignedMemory<tt, Alignment::SSE>(n);
  auto ptr_avx = AllocateAlignedMemory<tt, Alignment::AVX>(n);

  // check align
  ASSERT_TRUE(SSEAligned(ptr_sse));
  ASSERT_TRUE(AVXAligned(ptr_avx));

  // check size
  ASSERT_TRUE(malloc_size(ptr_sse) >= memory_used);
  ASSERT_TRUE(malloc_size(ptr_avx) >= memory_used);

  // check reallocate
  auto ptr_sse_to_avx =
      ReallocateAlignedMemory<tt, Alignment::AVX>(ptr_sse, rn);
  auto ptr_avx_to_sse =
      ReallocateAlignedMemory<tt, Alignment::SSE>(ptr_avx, rn);

  ASSERT_TRUE(SSEAligned(ptr_avx_to_sse));
  ASSERT_TRUE(AVXAligned(ptr_sse_to_avx));

  DeallocateAlignedMemory(ptr_sse_to_avx);
  DeallocateAlignedMemory(ptr_avx_to_sse);

  // check that all pointer is null size
  ASSERT_TRUE(malloc_size(ptr_sse) == 0);
  ASSERT_TRUE(malloc_size(ptr_avx) == 0);
  ASSERT_TRUE(malloc_size(ptr_sse_to_avx) == 0);
  ASSERT_TRUE(malloc_size(ptr_avx_to_sse) == 0);
}
