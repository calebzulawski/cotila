#ifndef COTILA_LEVEL1_H_
#define COTILA_LEVEL1_H_

#include <algorithm>
#include <cotila/apply_operations.h>
#include <cotila/scalar.h>
#include <cotila/type_traits.h>
#include <cotila/vector.h>
#include <functional>

namespace cotila {

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(const vector<T, N> &v, T a) {
  return detail::elementwise_unary(std::plus<T>(), v, a);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(T a, const vector<T, N> &v) {
  return detail::elementwise_unary(std::plus<T>(), v, a);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator+(const vector<T, N> &v1,
                                 const vector<T, N> &v2) {
  return detail::elementwise_binary(std::plus<T>(), v1, v2);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(const vector<T, N> &v, T a) {
  return detail::elementwise_unary(std::multiplies<T>(), v, a);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(T a, const vector<T, N> &v) {
  return detail::elementwise_unary(std::multiplies<T>(), v, a);
}

template <typename T, std::size_t N>
constexpr vector<T, N> operator*(const vector<T, N> &v1,
                                 const vector<T, N> &v2) {
  return detail::elementwise_binary(std::multiplies<T>(), v1, v2);
}

template <typename T, std::size_t N>
constexpr vector<T, N> conj(const vector<T, N> &v) {
  return detail::elementwise_unary(conj<T>, v);
}

template <typename T, std::size_t N>
constexpr vector<T, N> sqrt(const vector<T, N> &v) {
  return detail::elementwise_unary(static_cast<T (*)(T)>(sqrt), v);
}

template <typename T, std::size_t N>
constexpr vector<detail::scalar_type_t<T>, N> abs(const vector<T, N> &v) {
  return detail::elementwise_unary(abs<T>, v);
}

template <typename T, std::size_t N, typename F, typename U>
constexpr U accumulate(const vector<T, N> &v, U init, F &&f) {
  U r = init;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    r = std::apply(std::forward<F>(f), std::forward_as_tuple(r, v[i]));
  return r;
}

template <typename T, std::size_t N>
constexpr T dot(const vector<T, N> &a, const vector<T, N> &b) {
  T r = 0;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    r += a[i] * b[i];
  return r;
}

template <typename T, std::size_t N> constexpr T sum(const vector<T, N> &v) {
  return accumulate(v, 0, std::plus<T>());
}

template <typename T, std::size_t N> constexpr T min(const vector<T, N> &v) {
  return accumulate(v, v[0], [](T a, T b) { return std::min(a, b); });
}

template <typename T, std::size_t N> constexpr T max(const vector<T, N> &v) {
  return accumulate(v, v[0], [](T a, T b) { return std::max(a, b); });
}

template <typename T, std::size_t N>
constexpr std::size_t min_index(const vector<T, N> &v) {
  T min = v[0];
  std::size_t index = 0;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    if (v[i] < min) {
      index = i;
      min = v[i];
    }
  return index;
}

template <typename T, std::size_t N>
constexpr std::size_t max_index(const vector<T, N> &v) {
  T max = v[0];
  std::size_t index = 0;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    if (v[i] > max) {
      index = i;
      max = v[i];
    }
  return index;
}

template <typename T, typename U, std::size_t N>
constexpr vector<T, N> cast(const vector<U, N> &v) {
  auto cast_op = [](const U u) { return static_cast<T>(u); };
  return detail::elementwise_unary(cast_op, v);
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
  return detail::elementwise_unary(f, iota<N, std::size_t>());
}

} // namespace cotila

#endif // COTILA_LEVEL1_H_
