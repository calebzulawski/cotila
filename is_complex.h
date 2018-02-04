#ifndef COTILA_IS_COMPLEX_H_
#define COTILA_IS_COMPLEX_H_

#include <complex>
#include <type_traits>

namespace cotila {
template <class T> struct is_complex : std::false_type {};
template <class T> struct is_complex<std::complex<T>> : std::true_type {};
} // namespace cotila

#endif // COTILA_IS_COMPLEX_H_
