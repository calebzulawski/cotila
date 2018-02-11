#ifndef COTILA_VECTOR_OPERATORS_H_
#define COTILA_VECTOR_OPERATORS_H_

#include <cotila/vector/vector.h>

namespace cotila {

template <typename T, std::size_t N>
constexpr bool operator==(const vector<T, N> &v1, const vector<T, N> &v2) {
  for (std::size_t i = 0; i < vector<T, N>::size; ++i) {
    if (v1[i] != v2[i])
      return false;
  }
  return true;
}

template <typename T, std::size_t N>
constexpr bool operator!=(const vector<T, N> &v1, const vector<T, N> &v2) {
  return !(v1 == v2);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(const vector<T, N> &v, T a) {
  return elementwise([a](T x) { return x + a; }, v);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(T a, const vector<T, N> &v) {
  return elementwise([a](T x) { return a + x; }, v);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(const vector<T, N> &v1,
                                 const vector<T, N> &v2) {
  return elementwise(std::plus<T>(), v1, v2);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(const vector<T, N> &v, T a) {
  return elementwise([a](T x) { return x * a; }, v);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(T a, const vector<T, N> &v) {
  return elementwise([a](T x) { return a * x; }, v);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(const vector<T, N> &v1,
                                 const vector<T, N> &v2) {
  return elementwise(std::multiplies<T>(), v1, v2);
}

} // namespace cotila

#endif // COTILA_VECTOR_OPERATORS_H_
