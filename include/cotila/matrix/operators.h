#ifndef COTILA_MATRIX_OPERATORS_H_
#define COTILA_MATRIX_OPERATORS_H_

#include <cotila/vector/vector.h>

namespace cotila {

/** \addtogroup matrix
 *  @{
 */

/** @brief checks equality of two matrices
 *  @param a an \f$ N \times M \f$ matrix of type T
 *  @param b an \f$ N \times M \f$ matrix of type T
 *  @return true if and only if \f$ \textbf{a}_{ij} = \textbf{b}_{ij}\ \forall i,j \in 1\ .. N \f$
 *
 *  Checks the equality of two matrices.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr bool operator==(const matrix<T, N, M> &a,
                          const matrix<T, N, M> &b) {
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < M; ++j) {
      if (a.at(i, j) != b.at(i, j))
        return false;
    }
  }
  return true;
}

/** @brief checks inequality of two matrices
 *  @param a an \f$ N \times M \f$ matrix of type T
 *  @param b an \f$ N \times M \f$ matrix of type T
 *  @return false if and only if \f$ \textbf{a}_{ij} = \textbf{b}_{ij}\ \forall i,j \in 1\ .. N \f$
 *
 *  Checks the inequality of two matrices.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr bool operator!=(const matrix<T, N, M> &a,
                          const matrix<T, N, M> &b) {
  return !(a == b);
}

/** @brief computes the sum of a matrix and a scalar
 *  @param m an \f$ N \times M \f$ matrix of type T
 *  @param a a scalar of type T
 *  @return \f$ \textbf{m} + a \f$ such that \f$ \left(\textbf{m} + a\right)_{ij} = \textbf{m}_{ij} + a \f$
 *
 *  Computes the sum of a matrix and a scalar.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator+(const matrix<T, N, M> &m, T a) {
  return elementwise([a](T x) { return x + a; }, m);
}

/** @brief computes the sum of a matrix and a scalar
 *  @param a a scalar of type T
 *  @param m an \f$ N \times M \f$ matrix of type T
 *  @return \f$ a + \textbf{m} \f$ such that \f$ \left(a + \textbf{m}\right)_{ij} = a + \textbf{m}_{ij} \f$
 *
 *  Computes the sum of a matrix and a scalar.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator+(T a, const matrix<T, N, M> &m) {
  return elementwise([a](T x) { return a + x; }, m);
}

/** @brief computes the matrix sum
 *  @param a an \f$ N \times M \f$ matrix of type T
 *  @param b an \f$ N \times M \f$ matrix of type T
 *  @return \f$ \textbf{a} + \textbf{b} \f$ such that \f$ \left(\textbf{a} + \textbf{b}\right)_{ij} = \textbf{a}_{ij} + \textbf{b}_{ij} \f$
 *
 *  Computes the vector sum.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator+(const matrix<T, N, M> &a,
                                    const matrix<T, N, M> &b) {
  return elementwise(std::plus<T>(), a, b);
}

/** @brief computes the product of a matrix and a scalar
 *  @param m an \f$ N \times M \f$ matrix of type T
 *  @param a a scalar of type T
 *  @return \f$ \textbf{m}a \f$ such that \f$ \left(\textbf{m} a\right)_{ij} = \textbf{m}_{ij} a \f$
 *
 *  Computes the sum of a matrix and a scalar.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator*(const matrix<T, N, M> &m, T a) {
  return elementwise([a](T x) { return x * a; }, m);
}

/** @brief computes the product of a matrix and a scalar
 *  @param a a scalar of type T
 *  @param m an \f$ N \times M \f$ matrix of type T
 *  @return \f$ a\textbf{m} \f$ such that \f$ \left(a\textbf{m}\right)_{ij} = a\textbf{m}_{ij} \f$
 *
 *  Computes the sum of a matrix and a scalar.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator*(T a, const matrix<T, N, M> &m) {
  return elementwise([a](T x) { return a * x; }, m);
}

/** @brief computes the Hadamard product
 *  @param a an \f$ N \times M \f$ matrix of type T
 *  @param b an \f$ N \times M \f$ matrix of type T
 *  @return \f$ \textbf{a} \circ \textbf{b} \f$ such that \f$ \left(\textbf{a} \circ \textbf{b}\right)_{ij} = \textbf{a}_{ij} \textbf{b}_{ij} \f$
 *
 *  Computes the Hadamard, or elementwise, product of two vectors.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator*(const matrix<T, N, M> &a,
                                    const matrix<T, N, M> &b) {
  return elementwise(std::multiplies<T>(), a, b);
}

/** @brief computes the quotient between a matrix and a scalar
 *  @param m an \f$ N \times M \f$ matrix of type T
 *  @param a a scalar of type T
 *  @return \f$ \textbf{m}/a \f$ such that \f$ \left(\textbf{m}/a\right)_{ij} = \frac{\textbf{m}_{ij}}{a} \f$
 *
 *  Computes division between a matrix and a scalar.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator/(T a, const matrix<T, N, M> &m) {
  return elementwise([a](T x) { return a / x; }, m);
}

/** @brief computes the elementwise matrix quotient
 *  @param a an \f$ N \times M \f$ matrix of type T
 *  @param b an \f$ N \times M \f$ matrix of type T
 *  @return \f$ \textbf{a} \circ \textbf{b}' \f$ such that \f$ {\textbf{b}_{ij}}' = \left(\textbf{b}_{ij}\right)^{-1}\f$
 *  and \f$ \left(\textbf{a} \circ \textbf{b}'\right)_{ij} = \textbf{a}_{ij} {\textbf{b}'}_{ij} \f$
 *
 *  Computes elementwise division between two matrices
 */
template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator/(const matrix<T, N, M> &a,
                                    const matrix<T, N, M> &b) {
  return elementwise(std::divides<T>(), a, b);
}

/** }@*/

} // namespace cotila

#endif // COTILA_VECTOR_OPERATORS_H_
