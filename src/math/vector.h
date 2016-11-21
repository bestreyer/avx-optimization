#ifndef BSTR_MATH_VECTOR
#define BSTR_MATH_VECTOR

#include "../memory/alignment.h"
#include "add.h"
#include "div.h"
#include "macro.h"
#include "multiplication.h"
#include "sub.h"
#include <stdexcept>
#include <stdio.h>
#include <utility>

namespace mem = ::Bstr::Memory;

namespace Bstr {
namespace Math {
template <typename T> class Vector {
private:
  // How many items can be stored in 256 bits ?)
  static constexpr size_t _blockSize = 32 / sizeof(T);

private:
  T *_data;
  size_t _capacity;
  size_t _len;

private:
  // val up to _blockSize
  size_t roundToBlockSize(size_t val) {
    if (val % _blockSize != 0)
      val += _blockSize - val % _blockSize;
    return val;
  }

  void setCapacity(size_t newCapacity) {
    _capacity = roundToBlockSize(newCapacity);
  }

  void allocateDataMemoryByCapacity() {
    _data = mem::AllocateAlignedMemory<T, mem::Alignment::AVX>(_capacity);
  }

  void allocateMoreMemory() {
    _capacity *= 2;
    _data = mem::ReallocateAlignedMemory(_data, _capacity);
  }

  void _move(Vector &&other) {
    _capacity = std::exchange(other._capacity, 0);
    _len = std::exchange(other._len, 0);
    _data = std::exchange(other._data, nullptr);
  }

  Vector applyOperation(Vector &other, void (*func)(T *, T *, T *)) {
    if (other._len != _len)
      throw std::invalid_argument("Vectors must be have equals length");

    auto l = roundToBlockSize(_len);
    auto dataResult = mem::AllocateAlignedMemory<T, mem::Alignment::AVX>(l);

    auto iterations = l / _blockSize;
    for (size_t i = 0; i < iterations; i++) {
      size_t section = i * _blockSize;
      func(_data + section, other._data + section, dataResult + section);
    }
    return Vector(l, dataResult);
  }

public:
  Vector(size_t capacity) : _len(0) {
    setCapacity(capacity);
    allocateDataMemoryByCapacity();
  }

  Vector(size_t len, T *data) : _data(data), _capacity(len), _len(len) {}
  Vector() : Vector(_blockSize) {}

  Vector(Vector &&other) noexcept { _move(std::move(other)); }

  Vector &operator=(const Vector &other) {
    if (other._capacity != _capacity) {
      mem::DeallocateAlignedMemory(_data);
      _capacity = other._capacity;
      allocateDataMemoryByCapacity();
    }
    memcpy(_data, other._data, other._len * sizeof(T));
    return *this;
  }

  Vector &operator=(Vector &&other) {
    mem::DeallocateAlignedMemory(_data);
    _move(std::move(other));
    return *this;
  }

  Vector operator+(Vector &other) { return applyOperation(other, &add); }

  Vector operator*(Vector &other) {
    return applyOperation(other, &multiplication);
  }

  Vector operator-(Vector &other) { return applyOperation(other, &sub); }
  Vector operator/(Vector &other) { return applyOperation(other, &div); }

  T &operator[](size_t i) { return _data[i]; }

  void push(T element) {
    if (_len == _capacity)
      allocateMoreMemory();
    _data[_len++] = element;
  }

  ~Vector() { mem::DeallocateAlignedMemory(_data); }
};
}
}

#endif // BSTR_MATH_VECTOR
