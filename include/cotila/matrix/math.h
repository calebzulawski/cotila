#ifndef COTILA_MATRIX_MATH_H_
#define COTILA_MATRIX_MATH_H_

#include <cotila/scalar/math.h>
#include <cotila/matrix/matrix.h>
#include <cotila/vector/vector.h>
#include <cotila/vector/math.h>

namespace cotila {

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> conj(const matrix<T, N, M> &m) {
  return elementwise(cotila::conj<T>, m);
}

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

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, N, M> hermitian(const matrix<T, N, M> &m) {
  return transpose(conj(m));
}

template <typename T, std::size_t M, std::size_t N, std::size_t P>
constexpr matrix<T, N, M> matmul(const matrix<T, M, N> &m1,
                                 const matrix<T, N, P> &m2) {
  matrix<T, N, M> matmul = {};
  for (std::size_t i = 0; i < M; ++i) {
    for (std::size_t j = 0; j < P; ++j) {
      matmul[i][j] = cotila::dot(m1.row(i), cotila::conj(m2.column(j)));
    }
  }
  return matmul;
}

} // namespace cotila

#endif // COTILA_MATRIX_MATH_H_
