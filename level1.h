#ifndef COTILA_LEVEL1_H_
#define COTILA_LEVEL1_H_

#include "vector.h"

namespace cotila {

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(const vector<T, N> &v, T a) {
  auto mul = [a](auto... x) { return make_vector((a * x)...); };
  return std::apply(mul, v.to_array());
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
