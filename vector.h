#ifndef COTILA_VECTOR_H_
#define COTILA_VECTOR_H_

#include "tmp.h"
#include <array>
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
  return vector<typename all_same_type<Args...>::type, sizeof...(Args)>(
      args...);
}

template <typename T, std::size_t N>
constexpr bool operator==(const vector<T, N> &v1, const vector<T, N> &v2) {
  for (std::size_t i = 0; i < vector<T, N>::size; ++i) {
    if (v1[i] != v2[i])
      return false;
  }
  return true;
}

template <typename T, std::size_t N>
constexpr bool operator!=(const vector<T, N> &v1, const vector<T, N> &v2) {
  return !(v1 == v2);
}

} // namespace cotila

#endif // COTILA_VECTOR_H_
