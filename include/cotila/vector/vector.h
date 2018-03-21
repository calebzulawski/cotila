/** @file
 *  @brief Contains the definition of the `cotila::vector` class.
 */

#ifndef COTILA_VECTOR_VECTOR_H_
#define COTILA_VECTOR_VECTOR_H_

#include <array>
#include <cotila/detail/tmp.h>
#include <cstddef>

namespace cotila {

/** @brief A container representing a vector
 *  @tparam T scalar type to contain
 *  @tparam N size of the vector
 *
 *  `cotila::vector` is a container representing a vector.
 *
 *  It is an aggregate type similar to `std::array`, and can be initialized with
 *  aggregate initialization or with the `cotila::make_vector` function.
 */
template <typename T, std::size_t N> struct vector {
  static_assert(N != 0, "vector must contain at least one element");

  using value_type = T;
  using size_type = std::size_t;
  static constexpr size_type size = N; ///< @brief size of the vector

  /** @name Element access */
  ///@{
  /** @brief access specified element
   *  @param i position of the scalar element
   *  @return the requested scalar element
   *
   *  Returns a reference to the scalar element in position `i`, without bounds checking.
   */
  constexpr T &operator[](size_type i) noexcept { return array[i]; }

  /// @copydoc operator[]
  constexpr const T &operator[](size_type i) const noexcept { return array[i]; }
  ///@}

  /** @name Iterators */
  ///@{
  /** @brief returns an iterator to the beginning
   *  @return an iterator to the beginning
   *
   *  Returns an iterator to the beginning of the vector.
   */
  constexpr T *begin() noexcept { return array; }

  /** @brief returns an iterator to the end
   *  @return an iterator past the end
   *
   *  Returns an iterator to the end of the vector.
   */
  constexpr T *end() noexcept { return array + N; }

  /// @copydoc begin
  constexpr const T *cbegin() const noexcept { return array; }

  /// @copydoc end
  constexpr const T *cend() const noexcept { return array + N; }
  ///@}

  T array[N]; ///< @private
};

/** \addtogroup vector
 *  @{
 */

/** @brief constructs a `cotila::vector` from arguments
 *  @param args scalar elements to combine into a vector
 *  @return a vector containing `args`
 *  @relatesalso cotila::vector
 *
 *  Constructs a vector from its arguments, checking that all arguments are of
 *  the same type.
 */
template <typename... Args> constexpr decltype(auto) make_vector(Args... args) {
  return vector<typename detail::all_same_type<Args...>::type, sizeof...(Args)>{
      args...};
}

/** @}*/

} // namespace cotila

#endif // COTILA_VECTOR_VECTOR_H_
