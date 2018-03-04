/** @file
 * Mathematical operations on matrices.
 */
#ifndef COTILA_MATRIX_MATH_H_
#define COTILA_MATRIX_MATH_H_

#include <cotila/scalar/math.h>
#include <cotila/matrix/matrix.h>
#include <cotila/vector/vector.h>
#include <cotila/vector/math.h>

namespace cotila {

/**
 * Elementwise conjugate.
 * @param m an \f$N \times M\f$ matrix of type T.
 * @return a new matrix \f$\overline{\textbf{m}}\f$ such that
 * \f$\overline{m}_{ij} = {m}^{*}_{ji}\f$
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> conj(const matrix<T, N, M> &m) {
  return elementwise(cotila::conj<T>, m);
}

/**
 * Perform a transpose.
 * @param m an \f$N \times M\f$ matrix of type T.
 * @return \f$\textbf{m}^{\mathrm{T}}\f$, the transpose of \f$\textbf{m}\f$.
 * \f$\textbf{m}^{\mathrm{T}}_{ij} = \textbf{m}_{ji}\f$
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> transpose(const matrix<T, N, M> &m) {
  matrix<T, M, N> transposed = {};
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < M; ++j) {
      transposed[j][i] = m[i][j];
    }
  }
  return transposed;
}

/**
 * Perform a hermitian transpose.
 * @param m an \f$N \times M\f$ matrix of type T.
 * @return \f$\textbf{m}^{\mathrm{H}}\f$, the conjugate transpose of \f$\textbf{m}\f$.
 * \f$\textbf{m}^{\mathrm{H}}_{ij} = \textbf{m}^{*}_{ji}\f$
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> hermitian(const matrix<T, N, M> &m) {
  return transpose(conj(m));
}

/**
 * Matrix multiplication. Multiply two matrices containing elements of the same type T.
 * @param m1 An \f$M \times N\f$ dimensional matrix.
 * @param m2 An \f$N \times P\f$ dimensional matrix.
 * @return The matrix product \f$\textbf{A} = \textbf{m}_{1}\textbf{m}_{2}\f$ such that
 * \f$\textbf{A}_{ij} = \sum_{k=1}^{N}m_{1ik}m_{2kj}\f$
 */
template <typename T, std::size_t M, std::size_t N, std::size_t P>
constexpr matrix<T, N, M> matmul(const matrix<T, M, N> &m1,
                                 const matrix<T, N, P> &m2) {
  matrix<T, N, M> matmul = {};
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t j = 0; j < P; ++j) {
      matmul[i][j] = cotila::sum(m1.row(i)*m2.column(j));
    }
  }
  return matmul;
}

} // namespace cotila

#endif // COTILA_MATRIX_MATH_H_
