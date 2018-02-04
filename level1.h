#ifndef COTILA_LEVEL1_H_
#define COTILA_LEVEL1_H_

#include "apply_operations.h"
#include "vector.h"
#include <functional>

namespace cotila {

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(const vector<T, N> &v, T a) {
  return detail::elementwise_unary(std::plus<T>(), v, a);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(T a, const vector<T, N> &v) {
  return v + a;
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(const vector<T, N> &v1,
                                 const vector<T, N> &v2) {
  return detail::elementwise_binary(std::plus<T>(), v1, v2);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(const vector<T, N> &v, T a) {
  return detail::elementwise_unary(std::multiplies<T>(), v, a);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(T a, const vector<T, N> &v) {
  return v * a;
}

template <typename T, std::size_t N>
constexpr T dot(const vector<T, N> &a, const vector<T, N> &b) {
  T r = 0;
  for (int i = 0; i < vector<T, N>::size; ++i)
    r += a[i] * b[i];
  return r;
}

} // namespace cotila

#endif // COTILA_LEVEL1_H_
