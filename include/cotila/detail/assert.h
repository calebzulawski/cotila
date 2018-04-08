#ifndef COTILA_DETAIL_ASSERT_H_
#define COTILA_DETAIL_ASSERT_H_

#include <cotila/detail/type_traits.h>

#define COTILA_DETAIL_ASSERT_FLOATING_POINT(T)                                 \
  static_assert(std::is_floating_point<                                        \
                    typename cotila::detail::remove_complex<T>::type>::value,  \
                "argument must be a (real or complex) floating point type");

#define COTILA_DETAIL_ASSERT_INTEGRAL(T)                                       \
  static_assert(std::is_integral<T>::value,                                    \
                "argument must be a real integral type");

#define COTILA_DETAIL_ASSERT_VALID_COMPLEX(T)                                  \
  static_assert(                                                               \
      !cotila::detail::is_complex<T>::value ||                                 \
          std::is_floating_point<                                              \
              typename cotila::detail::remove_complex<T>::type>::value,        \
      "invalid complex type argument (valid types are "                        \
      "complex<float>, complex<double>, and complex<long double>)");

#define COTILA_DETAIL_ASSERT_ARITHMETIC(T)                                     \
  COTILA_DETAIL_ASSERT_VALID_COMPLEX(T);                                       \
  static_assert(std::is_arithmetic<                                            \
                    typename cotila::detail::remove_complex<T>::type>::value,  \
                "argument must be a (real or complex) arithmetic type");

#define COTILA_DETAIL_ASSERT_REAL(T)                                           \
  static_assert(std::is_arithmetic<T>::value,                                  \
                "argument must be a real arithmetic type");

#define COTILA_DETAIL_ASSERT_COMPLEX(T)                                        \
  COTILA_DETAIL_ASSERT_VALID_COMPLEX(T)                                        \
  static_assert(cotila::detail::is_complex<T>::value,                          \
                "argument must be a complex type");

#endif // COTILA_DETAIL_ASSERT_H_
