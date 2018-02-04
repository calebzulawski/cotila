#ifndef COTILA_TYPE_TRAITS_H_
#define COTILA_TYPE_TRAITS_H_

#include <complex>
#include <type_traits>

namespace cotila {
namespace detail {

template <typename T> struct is_complex : std::false_type {};
template <typename T> struct is_complex<std::complex<T>> : std::true_type {};
template <typename T> using is_complex_v = typename is_complex<T>::value;

template <typename T> struct scalar_type { using type = T; };
template <typename T> struct scalar_type<std::complex<T>> { using type = T; };
template <typename T> using scalar_type_t = typename scalar_type<T>::type;

} // namespace detail
} // namespace cotila

#endif // COTILA_TYPE_TRAITS_H_
