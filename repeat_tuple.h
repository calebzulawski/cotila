#ifndef COTILA_REPEAT_TUPLE_H_
#define COTILA_REPEAT_TUPLE_H_

#include <cstddef>
#include <tuple>

namespace cotila {

template <typename T, std::size_t N, typename... Types> struct repeat_tuple {
  using type = typename repeat_tuple<T, N - 1, Types..., T>::type;
};

template <typename T, typename... Types> struct repeat_tuple<T, 0, Types...> {
  using type = std::tuple<Types...>;
};

} // namespace cotila

#endif // COTILA_REPEAT_TUPLE_H_
