#ifndef BSTR_MEMORY_ALIGNMENT
#define BSTR_MEMORY_ALIGNMENT

#include <stdio.h>
#include <stdlib.h>

namespace Bstr {
namespace Memory {

// alignment's enum for sse, avx
// Example (allocate aligned memory for sse):
//  posix_memalign(pointer, static_cast<size_t>(Alignment::SSE), size);
enum class Alignment : size_t { DEFAULT = sizeof(void *), SSE = 16, AVX = 32 };

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

// Alias function allocate_aligned_memory<T, Alignment::AVX>
template <typename T>
constexpr auto avx_allocate_aligned_memory =
    allocate_aligned_memory<T, Alignment::AVX>;

// Alias function allocate_aligned_memory<T, Alignment::SSE>
template <typename T>
constexpr auto sse_allocate_aligned_memory =
    allocate_aligned_memory<T, Alignment::SSE>;

} // Memory namespace
} // Bstr namespace
#endif // BSTR_MEMORY_ALIGNMENT
