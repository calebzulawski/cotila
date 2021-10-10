/** @file
 *  @brief Contains the definition of the `cotila::matrix` class.
 */

#ifndef COTILA_MATRIX_MATRIX_H_
#define COTILA_MATRIX_MATRIX_H_

#include <array>
#include <cotila/matrix/utility.h>
#include <cotila/vector/vector.h>
#include <cotila/detail/assert.h>
#include <tuple>

namespace cotila {

/** @brief A container representing a matrix
 *  @tparam T scalar type to contain
 *  @tparam N number of rows
 *  @tparam M number of columns
 *
 *  `cotila::matrix` is a container representing a matrix.
 *  It is an aggregate type containing a single member array of type
 *  `T[N][M]` which can be initialized with aggregate initialization.
 */
template <typename T, std::size_t N, std::size_t M> struct matrix {
  static_assert(N != 0 && M != 0,
                "matrix must have have positive dimensions");
  COTILA_DETAIL_ASSERT_ARITHMETIC(T)

  using value_type = T;
  using size_type = std::size_t;
  static constexpr size_type column_size = N; ///< Number of rows
  static constexpr size_type row_size = M;    ///< Number of columns
  static constexpr size_type size = N * M;    ///< Number of elements

  /** @name Element access */
  ///@{
  /** @brief access specified row
   *  @param i index of the row to extract
   *  @return the selected row
   *
   *  Extracts a row from the matrix.
   */
  constexpr vector<T, M> row(std::size_t i) const {
    if (i >= N)
      throw std::out_of_range("Row index is out-of-range");
    return generate<M>([i, this](std::size_t j) { return arrays[i][j]; });
  }

  /** @brief access specified column
   *  @param i index of the column to extract
   *  @return the selected row
   *
   *  Extracts a column from the matrix
   */
  constexpr vector<T, N> column(std::size_t i) const {
    if (i >= M)
      throw std::out_of_range("Column index is out-of-range");
    return generate<N>([i, this](std::size_t j) { return arrays[j][i]; });
  }

  /**
   * @brief acess specified element
   * @param row selected line
   * @param column selected row
   * @return the selected scalar element
   *
   * Allow an access independent to the operator[],
   * ease the writing of generic algorithm
   */
  constexpr T &at(std::size_t row, std::size_t column = 0) {
    return get_real_by_name_impl(*this, row, column);
  }

  /**
   * @copydoc at
   */
  constexpr const T &at(std::size_t row, std::size_t column = 0) const {
    return get_real_by_name_impl(*this, row, column);
  }

  template <typename Self>
  static constexpr auto &get_real_by_name_impl(Self &self, std::size_t row, std::size_t column = 0) {
    if (row >= N || column >= M)
      throw "index out of range";
    return self.arrays[row][column];
  } ///< @private

  /** @brief access specified element
   *  @param i index of the row
   *  @return pointer to the specified row
   *
   *  This function returns a pointer to the specified row.  The intention
   *  of this function is to then access the specified element from the
   *  row pointer.  For a matrix `m`, accessing the element in the 5th row
   *  and 3rd column can be done with `m[5][3]`.
   */
  template <std::size_t L = M>
  typename std::enable_if<L == 1, T&>::type
  constexpr operator[](std::size_t i) { return arrays[i][0]; }

  /// @copydoc operator[]
  template <std::size_t L = M>
  typename std::enable_if<L == 1, const T&>::type
  constexpr operator[](std::size_t i) const { return arrays[i][0]; }

  /// @copydoc operator[]
  template <std::size_t L = M>
  typename std::enable_if<L != 1, T*>::type
  constexpr operator[](std::size_t i) { return arrays[i]; }

  /// @copydoc operator[]
  template <std::size_t L = M>
  typename std::enable_if<L != 1, const T*>::type
  constexpr operator[](std::size_t i) const { return arrays[i]; }
  ///@}

  /** @name Iterators */
  ///@{
  /** @brief returns an iterator to the beginning
   *  @return an iterator to the beginning
   *
   *  Returns an iterator to the beginning of the matrix.
   */
  constexpr T *begin() noexcept { return *arrays; }

  /** @brief returns an iterator to the end
   *  @return an iterator past the end
   *
   *  Returns an iterator to the end of the matrix.
   */
  constexpr T *end() noexcept { return *(arrays + size); }

  /// @copydoc begin
  constexpr const T *cbegin() const noexcept { return *arrays; }
  /// @copydoc begin
  constexpr const T *begin() const noexcept { return *arrays; }

  /// @copydoc end
  constexpr const T *cend() const noexcept { return *(arrays + size); }
  /// @copydoc end
  constexpr const T *end() const noexcept { return *(arrays + size); }
  ///@}

  constexpr operator vector<T, N>() const {
    vector<T, N> ret{};
    for (size_type i = 0; i < column_size; ++i)
            ret[i] = arrays[i][0];
    return ret;
  }

  template <typename U, std::size_t O, typename Container>
  friend constexpr matrix<U, O, 1> from_initializer(Container &);

  T arrays[N][M]; ///< @private
};

/** \addtogroup matrix
 *  @{
 */

template <typename T, std::size_t N, typename Container>
constexpr matrix<T, N, 1> from_initializer(Container & init) {
  if(std::size(init) != N)
    throw "The initializer has not the same size than the vector";

  matrix<T, N, 1> ret{};
  for (std::size_t i = 0; i < N; ++i)
    ret.arrays[i][0] = std::data(init)[i];

  return ret;
} ///< @private

/** @name cotila::matrix deduction guides */
///@{

/** @brief deduction guide for aggregate initialization
 *  @relatesalso cotila::matrix
 *
 *  This deduction guide allows cotila::matrix to be constructed like this:
 *  \code{.cpp}
 *  cotila::matrix m{{{1., 2.}, {3., 4.}}}; // deduces the type of m to be cotila::matrix<double, 2, 2>
 *  \endcode
 */
template <typename T, std::size_t M, std::size_t N>
matrix(const T (&)[M][N])->matrix<T, M, N>;

/** @brief deduction guide for complex-valued aggregate initialization
 *  @relatesalso cotila::matrix
 *
 *  This deduction guide allows cotila::matrix to be constructed like this:
 *  \code{.cpp}
 *  cotila::matrix m{{{{1., 0.}, {2., 1.}}, {{3., 2.}, {4., 3.}}}}; // deduces the type of m to be cotila::matrix<std::complex<double>, 2, 2>
 *  \endcode
 */
template <typename T, std::size_t M, std::size_t N>
matrix(const T (&)[M][N][2])->matrix<std::complex<T>, M, N>;

///@}

/** @}*/

} // namespace cotila

#endif // COTILA_MATRIX_MATRIX_H_
