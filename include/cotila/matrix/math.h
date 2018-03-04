/** @file
 *  @brief Mathematical operations on matrices.
 */
#ifndef COTILA_MATRIX_MATH_H_
#define COTILA_MATRIX_MATH_H_

#include <cotila/scalar/math.h>
#include <cotila/matrix/matrix.h>
#include <cotila/vector/vector.h>
#include <cotila/vector/math.h>

namespace cotila {

/** @brief computes the elementwise complex conjugate
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ M \times N \f$ matrix \f$\overline{\textbf{m}}\f$ such that
 *  \f$ \left(\overline{\textbf{m}}\right)_{ij} = \overline{\textbf{m}_{ij}},\ \forall i,j \f$
 *
 *  Computes the elementwise complex conjugate of a matrix
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> conj(const matrix<T, M, N> &m) {
  return elementwise(cotila::conj<T>, m);
}

/** @brief computes the transpose
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ N \times M \f$ matrix \f$ \textbf{m}^{\mathrm{T}} \f$ such that
 *  \f$ \left(\textbf{m}^{\mathrm{T}}\right)_{ij} = \textbf{m}_{ji},\ \forall i,j \f$
 *
 *  Computes the matrix transpose.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> transpose(const matrix<T, M, N> &m) {
  matrix<T, N, M> transposed = {};
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      transposed[j][i] = m[i][j];
    }
  }
  return transposed;
}

/** @brief computes the Hermitian transpose
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ N \times M \f$ matrix \f$ \textbf{m}^{*} \f$ such that
 *  \f$ \left(\textbf{m}^{*}\right)_{ij} = \overline{\textbf{m}_{ji}},\ \forall i,j \f$
 *
 *  Computes the Hermitian (conjugate) transpose.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> hermitian(const matrix<T, M, N> &m) {
  return transpose(conj(m));
}

/** @brief computes the matrix product
 *  @param a an \f$M \times N\f$ matrix
 *  @param b an \f$N \times P\f$ matrix
 *  @return an \f$ M \times P \f$ matrix \f$ \textbf{a}\textbf{b} \f$ such that
 *  \f$ \left(\textbf{ab}\right)_{ij} = \sum\limits_{k=1}^{N}\textbf{a}_{ik}\textbf{b}_{kj} \f$
 *
 *  Computes the product of two matrices.
 */
template <typename T, std::size_t M, std::size_t N, std::size_t P>
constexpr matrix<T, M, P> matmul(const matrix<T, M, N> &a,
                                 const matrix<T, N, P> &b) {
  matrix<T, M, P> matmul = {};
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t j = 0; j < P; ++j) {
      matmul[i][j] = cotila::sum(a.row(i)*b.column(j));
    }
  }
  return matmul;
}

} // namespace cotila

#endif // COTILA_MATRIX_MATH_H_
