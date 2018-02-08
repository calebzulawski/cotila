#ifndef COTILA_SCALAR_H_
#define COTILA_SCALAR_H_

#include <cotila/type_traits.h>
#include <type_traits>

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
constexpr typename std::enable_if<!detail::is_complex<T>::value, T>::type
abs(T x) {
  return x > 0 ? x : -x;
}

template <typename T>
constexpr typename std::enable_if<detail::is_complex<T>::value,
                                  typename T::value_type>::type
abs(T x) {
  return sqrt(x.real() * x.real() + x.imag() * x.imag());
}

constexpr double exponentiate(double x, int n) {
  if (n == 0)
    return 1;
  if (n < 0) {
    x = 1. / x;
    n = -n;
  }
  double y = 1.;
  while (n > 1) {
    if (n % 2 == 0) {
      n = n / 2.;
    } else {
      y *= x;
      n = (n - 1.) / 2.;
    }
    x *= x;
  }
  return x * y;
}

constexpr double nthroot(double x, int n) {
  if (x < 0)
    throw "nth root argument must be positive";
  double prev = -1;
  double est = 1;
  while (prev != est) {
    prev = est;
    double dxk = 1. / n * (x / exponentiate(prev, n - 1) - prev);
    est = prev + dxk;
  }
  return est;
}

template <typename T>
constexpr typename std::enable_if<!detail::is_complex<T>::value, T>::type
conj(T x) {
  return x;
}

template <typename T>
constexpr typename std::enable_if<detail::is_complex<T>::value, T>::type
conj(T x) {
  return {x.real(), -x.imag()};
}

} // namespace cotila

#endif // COTILA_SCALAR_H_
