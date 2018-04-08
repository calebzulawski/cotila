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
#include <cotila/detail/assert.h>

namespace cotila {

/** \addtogroup matrix
 *  @{
 */

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

/** @brief computes the elementwise real 
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ M \times N \f$ matrix \f$\textbf{m}\f$ of type T such that
 *  \f$ \left(\textbf{m}}_{ij} = \mathbb{R}\{\textbf{m}_{ij}\},\ \forall i,j \f$
 *
 *  Computes the elementwise real of a matrix
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<detail::remove_complex_t<T>, M, N>
real(const matrix<T, M, N> &m) {
  return elementwise([](auto i) { return std::real(i); }, m);
}

/** @brief computes the elementwise imag 
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ M \times N \f$ matrix \f$\textbf{m}\f$ of type T such that
 *  \f$ \left(\textbf{m}}_{ij} = \mathbb{I}\{\textbf{m}_{ij}\},\ \forall i,j \f$
 *
 *  Computes the elementwise imag of a matrix
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<detail::remove_complex_t<T>, M, N>
imag(const matrix<T, M, N> &m) {
  return elementwise([](auto i) { return std::imag(i); }, m);
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

/** @brief Computes the maximum absolute column sum norm
 *  @param m an \f$M \times N\f$ matrix
 *  @return a scalar \f$ {\left\lVert \textbf{m} \right\rVert}_1 \f$ of type T
 * such that \f$ {\left\lVert \textbf{m} \right\rVert}_1 = \max\limits_j
 * \sum\limits_{i=1}^M \left\lvert \textbf{m}_{ij} \right\rvert \f$
 *
 *  Computes the maximum absolute column sum norm of a matrix.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr T macs(const matrix<T, M, N> &m) {
  return max(
      generate<N>([&m](std::size_t i) { return sum(abs(m.column(i))); }));
}

/** @brief Computes the maximum absolute row sum norm
 *  @param m an \f$M \times N\f$ matrix
 *  @return a scalar \f$ {\left\lVert \textbf{m} \right\rVert}_\infty \f$ of
 * type T such that \f$ {\left\lVert \textbf{m} \right\rVert}_\infty = \max\limits_i
 * \sum\limits_{j=1}^N \left\lvert \textbf{m}_{ij} \right\rvert \f$
 *
 *  Computes the maximum absolute row sum norm of a matrix.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr T mars(const matrix<T, M, N> &m) {
  return max(generate<M>([&m](std::size_t i) { return sum(abs(m.row(i))); }));
}

/// @private
template <typename T, std::size_t M, std::size_t N>
constexpr std::tuple<matrix<T, M, N>, std::size_t, T>
gauss_jordan_impl(matrix<T, M, N> m, T tolerance) {
  COTILA_DETAIL_ASSERT_FLOATING_POINT(T);
  COTILA_DETAIL_ASSERT_REAL(T);

  // Define function for determining if an element is negligible
  auto negligible = [&tolerance](const T &v) { return abs(v) < tolerance; };

  T det = 1;
  std::size_t rank = 0;
  std::size_t i = 0, j = 0;
  while (i < M && j < N) {
    // Choose largest magnitude as pivot to avoid adding different magnitudes
    for (std::size_t ip = i + 1; ip < M; ++ip) {
      if (abs(m[ip][j]) > abs(m[i][j])) {
        for (std::size_t jp = 0; jp < N; ++jp) {
          auto tmp = m[ip][jp];
          m[ip][jp] = m[i][jp];
          m[i][jp] = tmp;
        }
        det *= -1;
        break;
      }
    }

    // If m_ij is still 0, continue to the next column
    if (!negligible(m[i][j])) {
      // Scale m_ij to 1
      auto s = m[i][j];
      for (std::size_t jp = 0; jp < N; ++jp)
        m[i][jp] /= s;
      det /= s;

      // Eliminate other values in the column
      for (std::size_t ip = 0; ip < M; ++ip) {
        if (ip == i)
          continue;
        if (!negligible(m[ip][j])) {
          auto s = m[ip][j];
          [&]() { // wrap this in a lambda to get around a gcc bug
            for (std::size_t jp = 0; jp < N; ++jp)
              m[ip][jp] -= s * m[i][jp];
          }();
        }
      }

      // Increment rank
      ++rank;

      // Select next row
      ++i;
    }
    ++j;
  }
  det = (rank == M) ? det : 0;
  return {m, rank, det};
}

/// @private
template <typename T, std::size_t M, std::size_t N>
constexpr std::tuple<matrix<T, M, N>, std::size_t, T>
gauss_jordan_impl(const matrix<T, M, N> &m) {
  T tol = std::max(N, M) * std::numeric_limits<T>::epsilon() * mars(m);
  return gauss_jordan_impl(m, tol);
}

/** @brief Compute the reduced row echelon form
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @return an \f$ M \times N \f$ matrix of type T, the reduced row echelon form
 * of \f$ \textbf{m} \f$
 *
 *  Computes the reduced row echelon form of a matrix using Gauss-Jordan
 * elimination.  The tolerance for determining negligible elements is \f$
 * \max\left(N, M\right) \cdot \epsilon \cdot {\left\lVert \textbf{m}
 * \right\rVert}_\infty \f$.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> rref(const matrix<T, M, N> &m) {
  return std::get<0>(gauss_jordan_impl(m));
}

/** @brief Compute the reduced row echelon form
 *  @param m an \f$ M \times N \f$ matrix of type T
 *  @param tolerance the tolerance used to determine when an element is
 * negligible (near zero)
 *  @return an \f$ M \times N \f$ matrix of type T, the reduced row echelon form
 * of \f$ \textbf{m} \f$
 *
 *  Computes the reduced row echelon form of a matrix using Gauss-Jordan
 * elimination.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> rref(const matrix<T, M, N> &m, T tolerance) {
  return std::get<0>(gauss_jordan_impl(m));
}

/** @brief Compute the rank
 *  @param m \f$ M \times N \f$ matrix of type T
 *  @return a scalar \f$ \textrm{rank}\left(\textbf{m}\right) \f$
 *
 *  Computes the rank using the reduced row echelon form.
 */
template <typename T, std::size_t M, std::size_t N>
constexpr std::size_t rank(const matrix<T, M, N> &m) {
  return std::get<1>(gauss_jordan_impl(m));
}

/** @brief Compute the determinant
 *  @param m \f$ M \times M \f$ matrix of type T
 *  @return a scalar \f$ \left\lvert \textbf{m} \right\rvert \f$ of type T
 *
 *  Computes the determinant using the reduced row echelon form.
 */
template <typename T, std::size_t M>
constexpr T det(const matrix<T, M, M> &m) {
  return std::get<2>(gauss_jordan_impl(m));
}

/** @brief computes the matrix inverse
 *  @param m an \f$ M \times M \f$ matrix of type T
 *  @return The inverse of \f$ \textbf{m} \f$, \f$ \textbf{m}^{-1}\f$ such that
 *  \f$ \textbf{m}\textbf{m}^{-1} = \textbf{m}^{-1}\textbf{m} = \textbf{I}_{M}
 * \f$
 *
 *  Computes the inverse of a matrix using the reduced row echelon form.
 */
template <typename T, std::size_t M>
constexpr matrix<T, M, M> inverse(const matrix<T, M, M> &m) {
  if (rank(m) < M)
    throw "matrix is not invertible";
  return submat<M, M>(rref(horzcat(m, identity<T, M>)), 0, M);
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

/** }@*/

} // namespace cotila

#endif // COTILA_MATRIX_MATH_H_
