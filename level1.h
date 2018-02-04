#ifndef COTILA_VECVEC_H_
#define COTILA_VECVEC_H_

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

template <typename Vec>
constexpr decltype(auto) dot(const Vec &a, const Vec &b) {
  typename Vec::value_type r = 0;
  for (int i = 0; i < Vec::size; ++i)
    r += a[i] * b[i];
  return r;
}

} // namespace cotila

#endif // COTILA_VECVEC_H_
