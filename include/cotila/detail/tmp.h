#ifndef COTILA_DETAIL_TMP_H_
#define COTILA_DETAIL_TMP_H_

#include <type_traits>

namespace cotila {
namespace detail {

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

template<typename T>
static auto test_callable(int)
        -> decltype(void(std::declval<T>()(std::declval<std::size_t>())), std::true_type{});
template<typename T>
static auto test_callable(long) -> std::false_type;

template<typename T>
struct is_callable_with_a_size_t : decltype(detail::test_callable<T>(0)){};

} // namespace detail
} // namespace cotila

#endif // COTILA_DETAIL_TMP_H_
