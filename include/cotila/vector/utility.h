#ifndef COTILA_VECTOR_UTILITY_H_
#define COTILA_VECTOR_UTILITY_H_

#include <cotila/vector/vector.h>
#include <tuple>

namespace cotila {

template <
    typename F, typename T, typename... Vectors,
    typename U = std::invoke_result_t<F, T, typename Vectors::value_type...>,
    std::size_t N =
        detail::all_same_value<std::size_t, Vectors::size...>::value>
constexpr vector<U, N> elementwise(F f, const vector<T, N> &v,
                                   const Vectors &... vectors) {
  std::array<U, N> op_applied = {};
  for (std::size_t i = 0; i < N; ++i)
    op_applied[i] = std::apply(f, std::forward_as_tuple(v[i], vectors[i]...));
  return op_applied;
}

template <typename T, std::size_t N, typename F, typename U>
constexpr U accumulate(const vector<T, N> &v, U init, F &&f) {
  U r = init;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    r = std::apply(std::forward<F>(f), std::forward_as_tuple(r, v[i]));
  return r;
}

template <typename T, typename U, std::size_t N>
constexpr vector<T, N> cast(const vector<U, N> &v) {
  return elementwise([](const U u) { return static_cast<T>(u); }, v);
}

template <std::size_t N, typename T>
constexpr vector<T, N> iota(T value = T()) {
  std::array<T, N> seq = {};
  for (auto &x : seq)
    x = value++;
  return seq;
}

template <std::size_t N, typename T>
constexpr vector<T, N> linspace(T min, T max) {
  return ((max - min) / (N - 1)) * iota<N, T>() + min;
}

template <std::size_t N, typename T> constexpr vector<T, N> fill(T value) {
  std::array<T, N> filled = {};
  for (auto &x : filled)
    x = value;
  return filled;
}

template <std::size_t N, typename F> constexpr decltype(auto) generate(F &&f) {
  return elementwise(f, iota<N, std::size_t>());
}

template <std::size_t N, typename T>
constexpr vector<T, N> rotate(vector<T, N> vec, int amt) {
  std::array<T, N> rotated = {};
  // add N (the modulus) to amt until it is positive
  while (amt < 0)
    amt += N;
  for (std::size_t i = 0; i < N; ++i)
    rotated[i] = vec[(i + amt) % N];
  return rotated;
}

template <std::size_t M, typename T, std::size_t N>
constexpr vector<T, M> slice(vector<T, N> vec, std::size_t start = 0) {

  std::array<T, M> sliced = {};
  for (std::size_t i = 0; i < M; ++i)
      sliced[i] = vec[i + start];

  return sliced;
}

} // namespace cotila

#endif // COTILA_VECTOR_UTILITY_H_
