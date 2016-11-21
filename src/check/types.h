#ifndef BSTR_TEMPLATE_TYPES
#define BSTR_TEMPLATE_TYPES

#include <cstddef>
#include <type_traits>

namespace Bstr {
namespace Check {

template <typename T> struct AllSign { static constexpr bool value = true; };

template <typename T, size_t size, typename Sign = AllSign<T>>
struct SizedTypeCheker {};

// Check the number is a float(size bytes) type
template <typename T, size_t size>
struct IsFloatSize : SizedTypeCheker<T, size> {
  static constexpr bool value =
      std::is_floating_point<T>::value && sizeof(T) == size;
};

// Check the number is an integral(size bytes) type
template <typename T, size_t size, typename Sign = AllSign<T>>
struct IsIntegralSize : SizedTypeCheker<T, size> {
  static constexpr bool value =
      std::is_integral<T>::value && sizeof(T) == size && Sign::value;
};

// Check the number is a float(32 bit) type
template <typename T> using IsFloat32 = IsFloatSize<T, 4>;
// Check the number is a float(64 bit) type
template <typename T> using IsFloat64 = IsFloatSize<T, 8>;
// Check the is an integral(8 bit) type
template <typename T> using IsIntegral8 = IsIntegralSize<T, 1>;
// Check the is an integral(16 bit) type
template <typename T> using IsIntegral16 = IsIntegralSize<T, 2>;
// Check the is an integral(32 bit) type
template <typename T> using IsIntegral32 = IsIntegralSize<T, 4>;
// Check the is an integral(64 bit) type
template <typename T> using IsIntegral64 = IsIntegralSize<T, 8>;

// Check the is an unsigned integral(8 bit) type
template <typename T>
using IsUIntegral8 = IsIntegralSize<T, 1, std::is_unsigned<T>>;
// Check the is an unsigned integral(16 bit) type
template <typename T>
using IsUIntegral16 = IsIntegralSize<T, 2, std::is_unsigned<T>>;
// Check the is an unsigned integral(32 bit) type
template <typename T>
using IsUIntegral32 = IsIntegralSize<T, 4, std::is_unsigned<T>>;
// Check the is an unsigned integral(64 bit) type
template <typename T>
using IsUIntegral64 = IsIntegralSize<T, 8, std::is_unsigned<T>>;

// Check the is an signed integral(8 bit) type
template <typename T>
using IsSIntegral8 = IsIntegralSize<T, 1, std::is_signed<T>>;
// Check the is an signed integral(16 bit) type
template <typename T>
using IsSIntegral16 = IsIntegralSize<T, 2, std::is_signed<T>>;
// Check the is an signed integral(32 bit) type
template <typename T>
using IsSIntegral32 = IsIntegralSize<T, 4, std::is_signed<T>>;
// Check the is an signed integral(64 bit) type
template <typename T>
using IsSIntegral64 = IsIntegralSize<T, 8, std::is_signed<T>>;
}
}
#endif // BSTR_TEMPLATE_TYPES
