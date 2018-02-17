#ifndef COTILA_MATRIX_MATH_H_
#define COTILA_MATRIX_MATH_H_

#include <cotila/matrix/matrix.h>

namespace cotila {

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

} // namespace cotila

#endif // COTILA_MATRIX_MATH_H_
