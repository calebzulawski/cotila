/** @file
 *  @brief Mathematical operations on scalar values
 */

#ifndef COTILA_SCALAR_MATH_H_
#define COTILA_SCALAR_MATH_H_

#include <cotila/detail/type_traits.h>
#include <cotila/detail/assert.h>
#include <type_traits>

namespace cotila {

/** \addtogroup scalar
 *  @{
 */

/** @brief computes the square root
 *  @param x argument
 *  @return \f$ \sqrt{x} \f$
 *
 *  Computes the square root.
 */
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

/** @brief computes the square root
 *  @param x argument
 *  @return \f$ \sqrt{x} \f$
 *
 *  Computes the square root.
 */
constexpr float sqrt(float x) { return sqrt(double(x)); }

/** @brief computes the absolute value
 *  @param x argument
 *  @return \f$ \lvert x \rvert \f$
 *
 *  Computes the absolute value.
 */
template <typename T> constexpr detail::remove_complex_t<T> abs(T x) {
  ASSERT_ARITHMETIC(T);
  if constexpr (detail::is_complex_v<T>)
    return sqrt(x.real() * x.real() + x.imag() * x.imag());
  else
    return x > 0 ? x : -x;
}

/** @brief computes exponents
 *  @param x base
 *  @param n exponent
 *  @return \f$ x^n \f$
 *
 *  Computes the exponentiation of a value to integer powers.
 */
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

/** @brief computes the \f$n\f$th root
 *  @param x argument
 *  @param n degree
 *  @return \f$ \sqrt[\leftroot{-2}\uproot{2}n]{x} \f$
 *
 *  Computes the \f$n\f$th root.
 */
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

/** @brief computes the complex conjugate
 *  @param x argument
 *  @return \f$ \bar{x} \f$
 *
 *  Computes the complex conjugate.
 */
template <typename T> constexpr T conj(T x) {
  ASSERT_ARITHMETIC(T);
  if constexpr (detail::is_complex_v<T>)
    return {x.real(), -x.imag()};
  else
    return x;
}

/** @}*/

} // namespace cotila

#endif // COTILA_SCALAR_MATH_H_
