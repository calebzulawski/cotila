#ifndef COTILA_DETAIL_TMP_H_
#define COTILA_DETAIL_TMP_H_

#include <type_traits>

namespace cotila {
namespace detail {

template <typename... Ts> struct all_same_type {};

template <typename T1, typename T2, typename... Ts>
struct all_same_type<T1, T2, Ts...> : all_same_type<T2, Ts...> {
  static_assert(std::is_same<T1, T2>::value,
                "All types in the template parameter list must be the same");
  using type = T1;
};

template <typename T> struct all_same_type<T> { using type = T; };

template <typename T, T... v> struct all_same_value {};

template <typename T, T v1, T v2, T... rest>
struct all_same_value<T, v1, v2, rest...> : all_same_value<T, v2, rest...> {
  static_assert(v1 == v2,
                "All values in the template parameter list must be equal");
  static constexpr T value = v1;
};

template <typename T, T v> struct all_same_value<T, v> {
  static constexpr T value = v;
};

} // namespace detail
} // namespace cotila

#endif // COTILA_TMP_H_
