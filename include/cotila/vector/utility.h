#ifndef COTILA_VECTOR_UTILITY_H_
#define COTILA_VECTOR_UTILITY_H_

#include <cotila/vector/vector.h>
#include <tuple>

namespace cotila {

/** \addtogroup vector
 *  @{
 */


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
 *  Concatenates two vectors.
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
