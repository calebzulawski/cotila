#ifndef COTILA_TMP_H_
#define COTILA_TMP_H_

#include <type_traits>

namespace cotila {

template <typename... Ts> struct all_same_type {};

template <typename T1, typename T2, typename... Ts>
struct all_same_type<T1, T2, Ts...> : all_same_type<T2, Ts...> {
  static_assert(std::is_same<T1, T2>::value,
                "All types in the template parameter list must be the same");
  using type = T1;
};

} // namespace cotila

#endif // COTILA_TMP_H_
