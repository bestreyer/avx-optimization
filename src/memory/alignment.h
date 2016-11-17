#ifndef BSTR_MEMORY_ALIGNMENT
#define BSTR_MEMORY_ALIGNMENT

#include "malloc_size.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Bstr {
namespace Memory {

// alignment's enum for sse, avx
// Example (allocate aligned memory for sse):
//  posix_memalign(pointer, static_cast<size_t>(Alignment::SSE), size);
enum class Alignment : size_t { DEFAULT = sizeof(void *), SSE = 16, AVX = 32 };

// check if address is aligned on a Aligment-byte boundary
template <Alignment A = Alignment::DEFAULT> inline bool is_aligned(void *ptr) {
  return ((uintptr_t)ptr & (static_cast<size_t>(A) - 1)) == 0;
}
// check if address is aligned on a 16-byte boundary
inline bool sse_aligned(void *ptr) { return is_aligned<Alignment::SSE>(ptr); }

// check if address is aligned on a 32-byte boundary
inline bool avx_aligned(void *ptr) { return is_aligned<Alignment::AVX>(ptr); }

// allocate aligned memory
// Example:
//  allocate_aligned_memory<int16_t, Alignment::AVX>(count_elements)
template <typename T, Alignment A = Alignment::DEFAULT>
inline T *allocate_aligned_memory(size_t count_elements) {
  void *ptr;
  ::posix_memalign(&ptr, static_cast<size_t>(A), count_elements * sizeof(T));
  return (T *)ptr;
}

// deallocate memory which allocate with allocate_aligned_memory
inline void deallocate_aligned_memory(void *ptr) noexcept { free(ptr); }

template <typename T, Alignment A = Alignment::DEFAULT>
inline T *reallocate_aligned_memory(T *old_ptr, size_t count_elements) {
  size_t old_size = ::malloc_size(static_cast<void *>(old_ptr));

  if (old_size > sizeof(T) * count_elements)
    return old_ptr;

  T *ptr = allocate_aligned_memory<T, A>(count_elements);
  ::memcpy(ptr, old_ptr, old_size);

  deallocate_aligned_memory(static_cast<void *>(old_ptr));
  return ptr;
}

} // Memory namespace
} // Bstr namespace
#endif // BSTR_MEMORY_ALIGNMENT
