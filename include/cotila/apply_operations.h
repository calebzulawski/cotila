#ifndef COTILA_APPLY_OPERATIONS_H_
#define COTILA_APPLY_OPERATIONS_H_

#include <cotila/vector.h>
#include <functional>
#include <tuple>
#include <type_traits>

namespace cotila {
namespace detail {

template <typename F, typename T, std::size_t N, std::size_t... I>
constexpr decltype(auto) elementwise_unary_impl(F &&f, const vector<T, N> &v,
                                                std::index_sequence<I...>) {
  return make_vector(std::apply(
      std::forward<F>(f), std::forward_as_tuple(std::get<I>(v.to_array())))...);
}

template <typename F, typename T, std::size_t N, typename... Args>
constexpr decltype(auto) elementwise_unary(F f, const vector<T, N> &v,
                                           Args &&... args) {
  auto op = [f, args = std::forward_as_tuple(args...)](T x) {
    return std::apply(f, std::tuple_cat(std::forward_as_tuple(x), args));
  };
  return elementwise_unary_impl(op, v, std::make_index_sequence<N>{});
}

template <typename F, typename T, std::size_t N, std::size_t... I>
constexpr decltype(auto) elementwise_binary_impl(F &&f, const vector<T, N> &v1,
                                                 const vector<T, N> &v2,
                                                 std::index_sequence<I...>) {
  return make_vector(
      std::apply(std::forward<F>(f),
                 std::forward_as_tuple(std::get<I>(v1.to_array()),
                                       std::get<I>(v2.to_array())))...);
}

template <typename F, typename T, std::size_t N, typename... Args>
constexpr decltype(auto) elementwise_binary(F f, const vector<T, N> &v1,
                                            const vector<T, N> &v2,
                                            Args &&... args) {
  auto op = [f, args = std::forward_as_tuple(args...)](T x, T y) {
    return std::apply(f, std::tuple_cat(std::forward_as_tuple(x, y), args));
  };
  return elementwise_binary_impl(op, v1, v2, std::make_index_sequence<N>{});
}

} // namespace detail
} // namespace cotila

#endif // COTILA_APPLY_OPERATIONS_H_
