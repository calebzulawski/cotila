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
  using array_type = std::array<T, N>;
  static constexpr size_type size = N;

  template <typename... Args>
  explicit constexpr vector(Args... args) : array{args...} {}

  constexpr vector(std::array<T, N> array) : array(array) {}

  constexpr const T &operator[](size_type i) const noexcept { return array[i]; }

  constexpr const array_type &to_array() const noexcept { return array; }

protected:
  std::array<T, N> array;
};

template <typename... Args> constexpr decltype(auto) make_vector(Args... args) {
  return vector<typename detail::all_same_type<Args...>::type, sizeof...(Args)>(
      args...);
}

} // namespace cotila

#endif // COTILA_VECTOR_VECTOR_H_