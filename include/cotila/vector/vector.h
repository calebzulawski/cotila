/** @file
 *  @brief Contains the definition of the `cotila::vector` class.
 */

#ifndef COTILA_VECTOR_VECTOR_H_
#define COTILA_VECTOR_VECTOR_H_

#include <array>
#include <initializer_list>
#include <cotila/detail/tmp.h>
#include <cotila/detail/assert.h>

namespace cotila {


template <typename T, std::size_t N, std::size_t M>
struct matrix;

template <typename T, std::size_t N, typename Container>
constexpr matrix<T, N, 1> from_initializer(Container &);

template <typename T, std::size_t N>
struct vector : public matrix<T, N, 1> {
  constexpr vector() = default;
  constexpr vector(const vector<T, N> &other) = default;
  constexpr vector(vector<T, N> &&other) noexcept = default;
  constexpr vector<T, N> &operator=(const vector<T, N> &other) = default;
  constexpr vector<T, N> &operator=(vector<T, N> &&other) noexcept = default;
  ~vector<T, N>() = default;

  constexpr vector(std::initializer_list<T> init) :
      matrix<T, N, 1>{from_initializer<T, N>(init)} {}

  constexpr operator matrix<T, N, 1>() {
    return matrix<T, N, 1>(*this);
  }
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
  return vector{args...};
}

/** @name cotila::vector deduction guides */
///@{

/** @brief deduction guide for uniform initialization
 *  @relatesalso cotila::vector
 *
 *  This deduction guide allows cotila::vector to be constructed like this:
 *  \code{.cpp}
 *  cotila::vector v{1., 2.}; // deduces the type of v to be cotila::vector<double, 2>
 *  \endcode
 */
template <typename T, typename... U>
vector(T, U...)
    ->vector<std::enable_if_t<(std::is_same_v<T, U> && ...), T>,
             1 + sizeof...(U)>;

/** @brief deduction guide for aggregate initialization
 *  @relatesalso cotila::vector
 *
 *  This deduction guide allows cotila::vector to be constructed like this:
 *  \code{.cpp}
 *  cotila::vector v{{1., 2.}}; // deduces the type of v to be cotila::vector<double, 2>
 *  \endcode
 */
template <typename T, std::size_t N> vector(const T (&)[N])->vector<T, N>;

/** @brief deduction guide for complex-valued aggregate initialization
 *  @relatesalso cotila::vector
 *
 *  This deduction guide allows cotila::vector to be constructed like this:
 *  \code{.cpp}
 *  cotila::vector v{{{1., 0}, {2., 1}}}; // deduces the type of v to be cotila::vector<std::complex<double>, 2>
 *  \endcode
 */
template <typename T, std::size_t N> vector(const T (&)[N][2])->vector<std::complex<T>, N>;

///@}

/** @}*/

} // namespace cotila

#endif // COTILA_VECTOR_VECTOR_H_
