#ifndef COTILA_MATRIX_UTILITY_H_
#define COTILA_MATRIX_UTILITY_H_

#include <cotila/matrix/matrix.h>
#include <tuple>

namespace cotila {

template <
    typename F, typename T, typename... Matrices,
    typename U = std::invoke_result_t<F, T, typename Matrices::value_type...>,
    std::size_t N =
        detail::all_same_value<std::size_t, Matrices::column_size...>::value,
    std::size_t M =
        detail::all_same_value<std::size_t, Matrices::row_size...>::value>
constexpr matrix<U, N, M> elementwise(F f, const matrix<T, N, M> &m,
                                      const Matrices &... matrices) {
  matrix<U, N, M> op_applied = {};
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < M; ++j) {
      op_applied[i][j] =
          std::apply(f, std::forward_as_tuple(m[i][j], matrices[i][j]...));
    }
  }
  return op_applied;
}

template <typename T, typename U, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> cast(const matrix<U, N, M> &m) {
  return elementwise([](const U u) { return static_cast<T>(u); }, m);
}

template <std::size_t N, std::size_t M, typename F>
constexpr decltype(auto) generate(F &&f) {
  matrix<std::invoke_result_t<F, std::size_t, std::size_t>, N, M> generated =
      {};
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < M; ++j) {
      generated[i][j] = std::apply(f, std::forward_as_tuple(i, j));
    }
  }
  return generated;
}

template <std::size_t N, std::size_t M, typename T>
constexpr matrix<T, N, M> fill(T value) {
  return generate<N, M>([value](std::size_t, std::size_t) { return value; });
}

} // namespace cotila

#endif // COTILA_MATRIX_UTILITY_H_
