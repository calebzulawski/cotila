#ifndef COTILA_VECTOR_H_
#define COTILA_VECTOR_H_

#include "repeat_tuple.h"

namespace cotila {

template <typename T, std::size_t N> class Vector {
public:
  template <typename... Args>
  explicit constexpr Vector(Args... args) : values(args...) {}

  template <std::size_t I> constexpr const T &get() const {
    return std::get<I>(values);
  }

protected:
  typename repeat_tuple<T, N>::type values;
};

} // namespace cotila

#endif // COTILA_VECTOR_H_
