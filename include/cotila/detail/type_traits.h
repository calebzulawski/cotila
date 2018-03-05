#ifndef COTILA_DETAIL_TYPE_TRAITS_H_
#define COTILA_DETAIL_TYPE_TRAITS_H_

#include <complex>
#include <type_traits>

namespace cotila {
namespace detail {

template <typename T> struct is_complex : std::false_type {};
template <typename T> struct is_complex<std::complex<T>> : std::true_type {};
template <typename T> constexpr bool is_complex_v = is_complex<T>::value;

template <typename T> struct remove_complex { using type = T; };
template <typename T> struct remove_complex<std::complex<T>> { using type = T; };
template <typename T> using remove_complex_t = typename remove_complex<T>::type;

} // namespace detail
} // namespace cotila

#endif // COTILA_DETAIL_TYPE_TRAITS_H_
