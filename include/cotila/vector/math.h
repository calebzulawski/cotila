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

/** \addtogroup vector
 *  @{
 */

/** @brief computes the dot product
 *  @param a an N-vector of type T
 *  @param b an N-vector of type T
 *  @return a scalar \f$ \textbf{a} \cdot \textbf{b} \f$ of type T such that
 *  \f$ \left(\textbf{a}\cdot\textbf{b}\right)_i = a_i \overline{b_i} \f$
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

/** @brief computes the index of the minimum valued element
 *  @param v an N-vector of type T
 *  @return an index \f$ i \f$ where \f$ v_i \leq v_j,\ \forall j \f$
 *
 *  Computes the index of the minimum valued element of a vector.
 *  Note: the return value is zero-indexed.
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
 *  @param v an N-vector of type T
 *  @return an index \f$ i \f$ where \f$ v_i \geq v_j,\ \forall j \f$
 *
 *  Computes the index of the maximum valued element of a vector.
 *  Note: the return value is zero-indexed.
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

/** @}*/

} // namespace cotila

#endif // COTILA_VECTOR_MATH_H_
