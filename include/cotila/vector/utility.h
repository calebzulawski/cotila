#ifndef COTILA_VECTOR_UTILITY_H_
#define COTILA_VECTOR_UTILITY_H_

#include <cotila/vector/vector.h>
#include <tuple>

namespace cotila {

/** \addtogroup vector
 *  @{
 */

/** @brief applies a function elementwise between many vectors
 *  @param f a function of type F that operates on many scalars of type T and returns a scalar of type U
 *  @param v an N-vector of type T
 *  @param vectors additional N-vectors of type T
 *  @return an N-vector of type T with elements described by \f$ f\left(\textbf{v}_i, \ldots\right) \f$
 *
 *  Applies a function elementwise between many vectors.
 */
template <
    typename F, typename T, typename... Vectors,
    typename U = std::invoke_result_t<F, T, typename Vectors::value_type...>,
    std::size_t N =
        detail::all_same_value<std::size_t, Vectors::size...>::value>
constexpr vector<U, N> elementwise(F f, const vector<T, N> &v,
                                   const Vectors &... vectors) {
  vector<U, N> op_applied = {};
  for (std::size_t i = 0; i < N; ++i)
    op_applied[i] = std::apply(f, std::forward_as_tuple(v[i], vectors[i]...));
  return op_applied;
}

/** @brief accumulates an operation across a vector
 *  @param v an N-vector of type T
 *  @param init the initial value
 *  @param f a function of type F that operates between U and vector elements of type T
 *  @return \f$ f\left(f\left(\ldots f\left(\textrm{init}, \textbf{v}_1\right), \ldots\right), \textbf{v}_N \right) \f$
 *
 *  Accumulates an operation over the elements.  This is equivalent to a functional fold.
 */
template <typename T, std::size_t N, typename F, typename U>
constexpr U accumulate(const vector<T, N> &v, U init, F &&f) {
  U r = init;
  for (std::size_t i = 0; i < vector<T, N>::size; ++i)
    r = std::apply(std::forward<F>(f), std::forward_as_tuple(r, v[i]));
  return r;
}

/** @brief casts a vector to another type
 *  @param v an N-vector of type U
 *  @return an N-vector of type T containing the casted elements of \f$ \textbf{v} \f$
 *
 *  Casts a vector to another type by `static_cast`ing each element.
 */
template <typename T, typename U, std::size_t N>
constexpr vector<T, N> cast(const vector<U, N> &v) {
  return elementwise([](const U u) { return static_cast<T>(u); }, v);
}

/** @brief generates a vector containing consecutive elements
 *  @param value the value of the first element of the vector
 *  @return an N-vector of type T such that \f$ \textbf{v}_i = \textrm{start} + i - 1 \f$
 *
 *  Generates a vector containing consecutive elements spaced by 1.
 */
template <std::size_t N, typename T>
constexpr vector<T, N> iota(T value = T()) {
  vector<T, N> seq = {};
  for (auto &x : seq)
    x = value++;
  return seq;
}

/** @brief generates a vector of equally spaced elements
 *  @param min the value of the first element of the vector
 *  @param max the value of the last element of the vector
 *  @return an N-vector of type T with elements spaced by \f$ \frac{\textbf{v}_N - \textbf{v}_1}{N-1} \f$
 *
 *  Generates a vector of equally spaced elements.
 */
template <std::size_t N, typename T>
constexpr vector<T, N> linspace(T min, T max) {
  return ((max - min) / (N - 1)) * iota<N, T>() + min;
}

/** @brief generates a vector containing a single value
 *  @param value the scalar value of all elements
 *  @return an N-vector of type T such that \f$ \textbf{v}_i = \textrm{value}\ \forall i \in 1\ .. N\f$
 *
 *  Generates a vector with all elements equal to a single value.
 */
template <std::size_t N, typename T> constexpr vector<T, N> fill(T value) {
  vector<T, N> filled = {};
  for (auto &x : filled)
    x = value;
  return filled;
}

/** @brief generates a vector as a function of its index
 *  @param f a function that operates on an integer index
 *  @return an N-vector with type matching the return type of f such that \f$ \textbf{v}_i = f(i) \f$
 *
 *  Generates a vector as a function of its index.
 */
template <std::size_t N, typename F> constexpr decltype(auto) generate(F &&f) {
  return elementwise(f, iota<N, std::size_t>());
}

/** @brief shifts vector elements
 *  @param v an N-vector of type T
 *  @param n the amount to shift each element
 *  @return an N-vector of type T \f$ \textbf{v} \gg n \f$ such that
 *  \f$ \left(\textbf{v} \gg n\right)_i = \textbf{v}_{(i + n)\ \textrm{mod}\ N} \f$
 *
 *  Rotates a vector by shifting its elements.
 */
template <std::size_t N, typename T>
constexpr vector<T, N> rotate(vector<T, N> v, int n) {
  vector<T, N> rotated = {};
  // add N (the modulus) to n until it is positive
  while (n < 0)
    n += N;
  for (std::size_t i = 0; i < N; ++i)
    rotated[i] = v[(i + n) % N];
  return rotated;
}

/** @brief slices a vector into a subvector
 *  @param v an N-vector of type T
 *  @param start the first index of the subvector
 *  @return an M-vector \f$ \textbf{v}_{\textrm{start}:\left(\textrm{start} + M - 1\right)} \f$
 *  such that  \f$ \left(\textbf{v}_{\textrm{start}:\left(\textrm{start} + M - 1\right)}\right)_i = \textbf{v}_{\textrm{start} + i} \f$
 *
 *  Slices a vector into a subvector.
 */
template <std::size_t M, typename T, std::size_t N>
constexpr vector<T, M> slice(vector<T, N> v, std::size_t start = 0) {

  vector<T, M> sliced = {};
  for (std::size_t i = 0; i < M; ++i)
      sliced[i] = v[i + start];

  return sliced;
}

/** @brief concatenates two vectors
 *  @param a an N-vector of type T
 *  @param b an M-vector of type T
 *  @return an N+M-vector \f$ \left[\textbf{a} \textbf{b}\right] \f$ such that
 *  \f$ \left(\left[\textbf{a} \textbf{b}\right]\right)_i = \begin{cases} \textbf{a}_i & i < N\\ \textbf{b}_{i - N} & i \ge N \end{cases} \f$
 *
 *  Slices a vector into a subvector.
 */
template <typename T, std::size_t N, std::size_t M>
constexpr vector<T, N + M> concat(vector<T, N> a, vector<T, M> b) {
  vector<T, N + M> concatted = {};
  for (std::size_t i = 0; i < N; ++i)
    concatted[i] = a[i];
  for (std::size_t i = 0; i < M; ++i)
    concatted[i + N] = b[i];
  return concatted;
}

/** }@*/

} // namespace cotila

#endif // COTILA_VECTOR_UTILITY_H_
