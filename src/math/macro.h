#ifndef BSTR_MATH_MACRO
#define BSTR_MATH_MACRO

// one type pointer to cast other type pointer and get value
#define CAST_GET_VAL(T, V) *(reinterpret_cast<T *>(V))

// check if unsigned number is power of 2
#define IS_POWER_2(N) ((N) & ((N)-1)) == 0

#endif // BSTR_MATH_MACRO
