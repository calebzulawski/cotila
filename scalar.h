#ifndef COTILA_SCALAR_H_
#define COTILA_SCALAR_H_

#include "type_traits.h"

namespace cotila {

constexpr double sqrt(double x) {
  if (x < 0)
    throw "sqrt argument must be positive";
  double prev = 0;
  double est = (1 + x) / 2;
  while (prev != est) {
    prev = est;
    est = (est + x / est) / 2;
  }
  return est;
}

constexpr float sqrt(float x) { return sqrt(double(x)); }

template <typename T>
constexpr std::enable_if_t<!detail::is_complex<T>::value, T> abs(T x) {
  return x > 0 ? x : -x;
}

template <typename T>
constexpr std::enable_if_t<detail::is_complex<T>::value, typename T::value_type>
abs(T x) {
  return sqrt(x.real() * x.real() + x.imag() * x.imag());
}

template <typename T>
constexpr std::enable_if_t<!detail::is_complex<T>::value, T> conj(T x) {
  return x;
}

template <typename T>
constexpr std::enable_if_t<detail::is_complex<T>::value, T> conj(T x) {
  return {x.real(), -x.imag()};
}

} // namespace cotila

#endif // COTILA_SCALAR_H_
