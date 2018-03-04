/** @file
 *  @brief Mathematical operations on vectors
 */

#ifndef COTILA_VECTOR_MATH_H_
#define COTILA_VECTOR_MATH_H_

#include <cotila/detail/type_traits.h>
#include <cotila/vector/utility.h>
#include <cotila/vector/vector.h>
#include <cotila/scalar/math.h>

namespace cotila {

/** @brief computes the elementwise complex conjugate
 *  @param v argument vector
 *  @return \f$ \bar{\textbf{v}} \f$
 *  @sa cotila::conj
 *
 *  Computes the elementwise complex conjugate of a vector.
 */
template <typename T, std::size_t N>
constexpr vector<T, N> conj(const vector<T, N> &v) {
  return elementwise(cotila::conj<T>, v);
}

/** @brief computes the elementwise square root
 *  @param v vector argument
 *  @return \f$ \begin{bmatrix} \sqrt{v_1} & \ldots &\sqrt{v_N} \end{bmatrix} \f$
 *
 *  Computes the elementwise square root of a vector.
 */
template <typename T, std::size_t N>
constexpr vector<T, N> sqrt(const vector<T, N> &v) {
  return elementwise(static_cast<T (*)(T)>(sqrt), v);
}

/** @brief computes the elementwise absolute value
 *  @param v vector argument
 *  @return \f$ \begin{bmatrix} \lvert v_1 \rvert & \ldots & \lvert v_N \rvert \end{bmatrix} \f$
 *
 *  Computes the elementwise absolute value of a vector.
 */
template <typename T, std::size_t N>
constexpr vector<detail::scalar_type_t<T>, N> abs(const vector<T, N> &v) {
  return elementwise(abs<T>, v);
}

/** @brief computes the dot product
 *  @param a first vector argument
 *  @param b second vector argument
 *  @return \f$ \textbf{a} \cdot \textbf{b} \f$
 *
 *  Computes the dot (inner) product of two vectors.
 */
template <typename T, std::size_t N>
constexpr T dot(const vector<T, N> &a, const vector<T, N> &b) {
  T r = 0;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    r += a[i] * conj(b[i]);
  return r;
}

/** @brief computes the sum of elements
 *  @param v vector argument
 *  @return \f$ \sum\limits_{i} v_i \f$
 *
 *  Computes the sum of the elements of a vector.
 */
template <typename T, std::size_t N> constexpr T sum(const vector<T, N> &v) {
  return accumulate(v, 0, std::plus<T>());
}

/** @brief computes the minimum valued element
 *  @param v vector argument
 *  @return \f$ v_i \f$ where \f$ v_i \leq v_j,\ \forall j \f$
 *
 *  Computes the minimum valued element of a vector.
 */
template <typename T, std::size_t N> constexpr T min(const vector<T, N> &v) {
  return accumulate(v, v[0], [](T a, T b) { return std::min(a, b); });
}

/** @brief computes the maximum valued element
 *  @param v vector argument
 *  @return \f$ v_i \f$ where \f$ v_i \geq v_j,\ \forall j \f$
 *
 *  Computes the maximum valued element of a vector.
 */
template <typename T, std::size_t N> constexpr T max(const vector<T, N> &v) {
  return accumulate(v, v[0], [](T a, T b) { return std::max(a, b); });
}


/** @brief computes the index of the minimum valued element
 *  @param v vector argument
 *  @return \f$ i \f$ where \f$ v_i \leq v_j,\ \forall j \f$
 *
 *  Computes the index of the minimum valued element of a vector.
 */
template <typename T, std::size_t N>
constexpr std::size_t min_index(const vector<T, N> &v) {
  T min = v[0];
  std::size_t index = 0;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    if (v[i] < min) {
      index = i;
      min = v[i];
    }
  return index;
}

/** @brief computes the index of the maximum valued element
 *  @param v vector argument
 *  @return \f$ i \f$ where \f$ v_i \geq v_j,\ \forall j \f$
 *
 *  Computes the index of the maximum valued element of a vector.
 */
template <typename T, std::size_t N>
constexpr std::size_t max_index(const vector<T, N> &v) {
  T max = v[0];
  std::size_t index = 0;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    if (v[i] > max) {
      index = i;
      max = v[i];
    }
  return index;
}

} // namespace cotila

#endif // COTILA_VECTOR_MATH_H_
