/** @file
 *  @brief Mathematical operations on matrices.
 */
#ifndef COTILA_MATRIX_MATH_H_
#define COTILA_MATRIX_MATH_H_

#include<algorithm>

#include <cotila/scalar/math.h>
#include <cotila/vector/vector.h>
#include <cotila/vector/math.h>
#include <cotila/matrix/matrix.h>
#include <cotila/matrix/utility.h>

namespace cotila {

/** @brief computes the elementwise complex conjugate
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ M \times N \f$ matrix \f$\overline{\textbf{m}}\f$ of type T such that
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
 *  @return an \f$ N \times M \f$ matrix \f$ \textbf{m}^{\mathrm{T}} \f$ of type T such that
 *  \f$ \left(\textbf{m}^{\mathrm{T}}\right)_{ij} = \textbf{m}_{ji},\ \forall i,j \f$
 *
 *  Computes the matrix transpose.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> transpose(const matrix<T, M, N> &m) {
  return generate<N, M>([&m](auto i, auto j){return m[j][i];});
}

/** @brief computes the Hermitian transpose
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ N \times M \f$ matrix \f$ \textbf{m}^{*} \f$ of type T such that
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
 *  @return an \f$ M \times P \f$ matrix \f$ \textbf{a}\textbf{b} \f$ of type T such that
 *  \f$ \left(\textbf{ab}\right)_{ij} = \sum\limits_{k=1}^{N}\textbf{a}_{ik}\textbf{b}_{kj} \f$
 *
 *  Computes the product of two matrices.
 */
template <typename T, std::size_t M, std::size_t N, std::size_t P>
constexpr matrix<T, M, P> matmul(const matrix<T, M, N> &a,
                                 const matrix<T, N, P> &b) {
  return generate<M, P>([&a, &b](auto i, auto j){return cotila::sum(a.row(i)*b.column(j));});
}

/** @brief Computes the kronecker tensor product
 *  @param a an \f$M \times N\f$ matrix
 *  @param b an \f$P \times Q\f$ matrix
 *  @return An \f$ MP \times NQ \f$ matrix \f$ \textbf{a}\otimes\textbf{b} \f$ of type T such that
 *  \f$ \left(\textbf{a}\otimes\textbf{b}\right)_{ij} = \textbf{a}_{\lfloor i/P \rfloor,\lfloor j/Q \rfloor}\textbf{b}_{i\textrm{%}P,j\textrm{%}Q} \f$
 *  where \f$ i \textrm{%} P \f$ is the remainder of \f$ i/P \f$ 
 *
 * Computes the kronecker tensor product of two matrices.
 */
template <typename T, std::size_t M, std::size_t N, 
                      std::size_t P, std::size_t Q>
constexpr matrix<T, M * P, N * Q> kron(const matrix<T, M, N> &a,
                                       const matrix<T, P, Q> &b) {
  return generate<M * P, N * Q>([&a, &b](auto i, auto j) { return a[i / P][j / Q] * b[i % P][j % Q]; });
}

/** @brief Perform Gaussian Elimination
 *  @param a an \f$ M \times M \f$ matrix of type T
 *  @param b A \f$ M \times N \f$ matrix of type T 
 *  @return The \f$ M \times N \f$ matrix \f$ \textbf{x} \f$ that solves the equation
 *  \f$ \textbf{a}\textbf{x} = \textbf{b} \f$.
 *
 *  Performs Gaussian elimination.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> gauss_elim(matrix<T, M, M> a,
                                     matrix<T, M, N> b) {
  for (std::size_t k = 0; k < M; ++k) {
    // first normalize the row
    auto scale_a = a[k][k];
    if (scale_a == 0)
      throw "Matrix on left hand side is not invertible";

    for (std::size_t j = 0; j < N; ++j) {
      b[k][j] = b[k][j] / scale_a;
      a[k][j] = a[k][j] / scale_a;
    }
    auto pivot_a = a.row(k);
    auto pivot_b = b.row(k);

    for (std::size_t i = 0; i < M; ++i) {
      if (i != k) {
        // pivot should be normalized to 1 already
        auto row_to_subtract_a = pivot_a * a[i][k];
        auto row_to_subtract_b = pivot_b * a[i][k];
        for (std::size_t j = 0; j < M; ++j) {
          a[i][j] = a[i][j] - row_to_subtract_a[j];
        }
        for (std::size_t j = 0; j < N; ++j) {
          b[i][j] = b[i][j] - row_to_subtract_b[j];
        }
      }
    }
  }
  return b;
}

/** @brief computes the matrix inverse
 *  @param m an \f$ M \times M \f$ matrix of type T
 *  @return The inverse of \f$ \textbf{m} \f$, \f$ \textbf{m}^{-1}\f$ such that
 *  \f$ \textbf{m}\textbf{m}^{-1} = \textbf{m}^{-1}\textbf{m} = \textbf{I}_{M}
 * \f$
 *
 *  Computes the inverse of a matrix.
 */
template <typename T, std::size_t M>
constexpr matrix<T, M, M> inverse(const matrix<T, M, M> &m) {
  return gauss_elim(m, identity<T, M>);
}

/** @brief computes the trace
 *  @param m an \f$ M \times M \f$ matrix of type T
 *  @return the trace of \f$ \textbf{m} \f$, \f$ \textrm{tr}\left(\textbf{m}\right) \f$
 *  such that \f$ \textrm{tr}\left(\textbf{m}\right) = \sum\limits_{n=1}^{M} \textbf{m}_{nn} \f$
 *
 *  Computes the trace of a matrix.
 */
template <typename T, std::size_t M>
constexpr T trace(const matrix<T, M, M> &m) {
  return sum(generate<M>([&m](std::size_t i){ return m[i][i]; }));
}

} // namespace cotila

#endif // COTILA_MATRIX_MATH_H_
