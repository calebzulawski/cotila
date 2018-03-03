#ifndef COTILA_VECTOR_VECTOR_H_
#define COTILA_VECTOR_VECTOR_H_

#include <array>
#include <cotila/detail/tmp.h>
#include <cstddef>

namespace cotila {

template <typename T, std::size_t N> class vector {
public:
  static_assert(N != 0, "vector must contain at least one element");

  using value_type = T;
  using size_type = std::size_t;
  static constexpr size_type size = N;

  constexpr T &operator[](size_type i) noexcept { return array[i]; }
  constexpr const T &operator[](size_type i) const noexcept { return array[i]; }

  constexpr T *begin() noexcept { return array; }
  constexpr T *end() noexcept { return array + N; }
  constexpr const T *cbegin() const noexcept { return array; }
  constexpr const T *cend() const noexcept { return array + N; }

  T array[N];
};

template <typename... Args> constexpr decltype(auto) make_vector(Args... args) {
  return vector<typename detail::all_same_type<Args...>::type, sizeof...(Args)>{
      args...};
}

} // namespace cotila

#endif // COTILA_VECTOR_VECTOR_H_
