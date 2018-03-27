#ifndef COTILA_MATRIX_UTILITY_H_
#define COTILA_MATRIX_UTILITY_H_

#include <cotila/matrix/matrix.h>
#include <tuple>

namespace cotila {

/** \addtogroup matrix
 *  @{
 */

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

template <typename T, std::size_t N>
constexpr matrix<T, N, N> identity
  = generate<N, N>([](std::size_t i, std::size_t j) { return T(i == j ? 1 : 0); });

template <std::size_t Row, std::size_t Col, std::size_t M, std::size_t N, typename T>
constexpr matrix<T, M * Row, N * Col> repmat(const matrix<T, M, N> &m) {
  return generate<M * Row, N * Col>([&m](std::size_t i, std::size_t j) {
    return m[i % M][j % N];
  });
}

template <std::size_t M, std::size_t N, typename T>
constexpr matrix<T, M, N> swaprow(const matrix<T, M, N> &m, std::size_t row1, std::size_t row2){
    auto A = m;
    for (int i = 0; i < N; i++)
    {
        T tmp = A[row1][i];
        A[row1][i] = A[row2][i];
        A[row2][i] = tmp;
    }
    return A;
}

template <std::size_t M, std::size_t N, typename T>
constexpr matrix<T, M, N> swapcol(const matrix<T, M, N> &m, std::size_t col1, std::size_t col2){
    auto A = m;
    for (int i = 0; i < N; i++)
    {
        T tmp = A[i][col1];
        A[i][col1] = A[i][col2];
        A[i][col2] = tmp;
    }
    return A;
}

template<std::size_t M, std::size_t N, std::size_t P, typename T>
constexpr matrix<T, M, N + P> horzcat(const matrix<T, M, N> &a, const matrix<T, M, P> &b){
    return generate<M, N+P>([&a, &b](std::size_t i, std::size_t j){
        return j < N ? a[i][j] : b[i][j - N];
    });
}

template<std::size_t M, std::size_t N, std::size_t P, typename T>
constexpr matrix<T, M + N, P> vertcat(const matrix<T, M, P> &a, const matrix<T, N, P> &b){
    return generate<M + N, P>([&a, &b](std::size_t i, std::size_t j){
        return i < M ? a[i][j] : b[i - M][j];
    });
}

template<std::size_t P, std::size_t Q, std::size_t M, std::size_t N, typename T>
constexpr matrix<T, P, Q> submat(const matrix<T, M, N> &m, std::size_t i, std::size_t j){
    if ((i + P > M) || (j + Q > N)) throw "index out of range";
    return generate<P, Q>([&m, &i, &j](std::size_t r, std::size_t c){
        return m[i + r][j + c];
    });
}

template <std::size_t P, std::size_t Q, std::size_t M, std::size_t N,
          typename T, typename = std::enable_if<P * Q == M * N>>
constexpr matrix<T, P, Q> reshape(const matrix<T, M, N> &m) {
  return generate<P, Q>([&m]<std::size_t Q1 = Q, std::size_t N1 = N>(
      std::size_t i, std::size_t j) {
    return m[(i * Q1 + j) / N][(i * Q1 + j) % N];
  });
}

/** }@*/

} // namespace cotila

#endif // COTILA_MATRIX_UTILITY_H_
