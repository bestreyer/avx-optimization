#ifndef BSTR_TEMPLATE_ENABLE
#define BSTR_TEMPLATE_ENABLE

#include "types.h"

namespace Bstr {
namespace Check {

// enable if type is float32
template <typename T, typename Q>
using EnableIfFloat32 = typename std::enable_if<IsFloat32<T>::value, Q>::type;

// enable if type is float64
template <typename T, typename Q>
using EnableIfFloat64 = typename std::enable_if<IsFloat64<T>::value, Q>::type;

// enable if type is int8_t, uint8_t
template <typename T, typename Q>
using EnableIfIntegral8 =
    typename std::enable_if<IsIntegral8<T>::value, Q>::type;

// enable if type is int16_t, uint16_t
template <typename T, typename Q>
using EnableIfIntegral16 =
    typename std::enable_if<IsIntegral16<T>::value, Q>::type;

// enable if type is int32_t, uint32_t
template <typename T, typename Q>
using EnableIfIntegral32 =
    typename std::enable_if<IsIntegral32<T>::value, Q>::type;

// enable if type is int64_t, uint64_t
template <typename T, typename Q>
using EnableIfIntegral64 =
    typename std::enable_if<IsIntegral64<T>::value, Q>::type;
}
}
#endif // BSTR_TEMPLATE_ENABLE
