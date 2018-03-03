#ifndef COTILA_MATRIX_MATRIX_H_
#define COTILA_MATRIX_MATRIX_H_

#include <array>
#include <cotila/vector/utility.h>
#include <cotila/vector/vector.h>
#include <tuple>

namespace cotila {

template <typename T, std::size_t N, std::size_t M> struct matrix {
  static_assert(N != 0 && M != 0,
                "matrix must have have positive dimensions");
  using value_type = T;
  using size_type = std::size_t;
  static constexpr size_type column_size = N;
  static constexpr size_type row_size = M;

  constexpr vector<T, M> row(std::size_t i) const {
    if (i >= N)
      throw "index out of range";
    return generate<M>([i, this](std::size_t j) { return arrays[i][j]; });
  }

  constexpr vector<T, N> column(std::size_t i) const {
    if (i >= M)
      throw "index out of range";
    return generate<M>([i, this](std::size_t j) { return arrays[j][i]; });
  }

  constexpr T *operator[](std::size_t i) { return arrays[i]; }
  constexpr T const *operator[](std::size_t i) const { return arrays[i]; }

  T arrays[N][M];
};

} // namespace cotila

#endif // COTILA_MATRIX_MATRIX_H_
