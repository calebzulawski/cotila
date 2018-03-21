#ifndef COTILA_MATRIX_OPERATORS_H_
#define COTILA_MATRIX_OPERATORS_H_

#include <cotila/vector/vector.h>

namespace cotila {

/** \addtogroup matrix
 *  @{
 */

template <typename T, std::size_t N, std::size_t M>
constexpr bool operator==(const matrix<T, N, M> &m1,
                          const matrix<T, N, M> &m2) {
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < M; ++j) {
      if (m1[i][j] != m2[i][j])
        return false;
    }
  }
  return true;
}

template <typename T, std::size_t N, std::size_t M>
constexpr bool operator!=(const matrix<T, N, M> &m1,
                          const matrix<T, N, M> &m2) {
  return !(m1 == m2);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator+(const matrix<T, N, M> &v, T a) {
  return elementwise([a](T x) { return x + a; }, v);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator+(T a, const matrix<T, N, M> &v) {
  return elementwise([a](T x) { return a + x; }, v);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator+(const matrix<T, N, M> &m1,
                                    const matrix<T, N, M> &m2) {
  return elementwise(std::plus<T>(), m1, m2);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator*(const matrix<T, N, M> &v, T a) {
  return elementwise([a](T x) { return x * a; }, v);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator*(T a, const matrix<T, N, M> &v) {
  return elementwise([a](T x) { return a * x; }, v);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator*(const matrix<T, N, M> &m1,
                                    const matrix<T, N, M> &m2) {
  return elementwise(std::multiplies<T>(), m1, m2);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator/(T a, const matrix<T, N, M> &v) {
  return elementwise([a](T x) { return a / x; }, v);
}

template <typename T, std::size_t N, std::size_t M>
constexpr matrix<T, N, M> operator/(const matrix<T, N, M> &m1,
                                    const matrix<T, N, M> &m2) {
  return elementwise(std::divides<T>(), m1, m2);
}

/** }@*/

} // namespace cotila

#endif // COTILA_VECTOR_OPERATORS_H_
