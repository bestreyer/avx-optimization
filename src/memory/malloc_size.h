#ifndef BSTR_MEMORY_MALLOC_SIZE
#define BSTR_MEMORY_MALLOC_SIZE

#ifdef __APPLE__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#define malloc_size malloc_usable_size
#endif //

#endif // BSTR_MEMORY_MALLOC_SIZE
