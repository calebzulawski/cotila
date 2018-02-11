#ifndef COTILA_APPLY_OPERATIONS_H_
#define COTILA_APPLY_OPERATIONS_H_

#include <cotila/vector.h>
#include <functional>
#include <tuple>
#include <type_traits>

namespace cotila {
namespace detail {

template <typename F, typename T, std::size_t N, typename... Args,
          typename FnType = std::invoke_result_t<F, T, Args...>>
constexpr vector<FnType, N> elementwise_unary(F f, const vector<T, N> &v,
                                              Args &&... args) {
  std::array<FnType, N> op_applied = {};
  for (std::size_t i = 0; i < N; ++i)
    op_applied[i] = std::apply(f, std::forward_as_tuple(v[i], args...));
  return op_applied;
}

template <typename F, typename T, std::size_t N, typename... Args,
          typename FnType = std::invoke_result_t<F, T, T, Args...>>
constexpr vector<FnType, N> elementwise_binary(F f, const vector<T, N> &v1,
                                               const vector<T, N> &v2,
                                               Args &&... args) {
  std::array<FnType, N> op_applied = {};
  for (std::size_t i = 0; i < N; ++i)
    op_applied[i] = std::apply(f, std::forward_as_tuple(v1[i], v2[i], args...));
  return op_applied;
}

} // namespace detail
} // namespace cotila

#endif // COTILA_APPLY_OPERATIONS_H_
