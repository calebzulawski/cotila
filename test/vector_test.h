#ifndef COTILA_VECTOR_TEST_H_
#define COTILA_VECTOR_TEST_H_

#include <complex>
#include <cotila/cotila.h>

namespace cotila {
namespace test {

static_assert(make_vector(1, 2, 3) == vector{1, 2, 3},
              "make_vector and uniform initialization deduction guide");

static_assert(make_vector(1, 2, 3) == vector{{1, 2, 3}},
              "make_vector and aggregate initialization deduction guide");

static_assert(
    make_vector(std::complex<double>(1), std::complex<double>(2),
                std::complex<double>(3)) ==
        vector{{{1., 0.}, {2., 0.}, {3., 0.}}},
    "make_vector and complex aggregate initialization deduction guide");

static_assert(elementwise([](double x) { return 1 / x; }, vector{1., 2., 4.}) ==
                  vector{1., 0.5, 0.25},
              "elementwise");

static_assert(vector{1, 2, 3} == vector{1, 2, 3}, "operator==");

static_assert(vector{1, 2, 3} != vector{3, 2, 1}, "operator!=");

static_assert(2 + vector{1, 2, 3} == vector{3, 4, 5}, "operator+");

static_assert(vector{1, 2, 3} + 2 == vector{3, 4, 5}, "operator+");

static_assert(vector{1, 2, 3} + vector{1, 2, 3} == vector{2, 4, 6},
              "operator+");

static_assert(conj(vector{{{-1., 2.}, {1., -2.}}}) ==
                  vector{{{-1., -2.}, {1., 2.}}},
              "conj");

static_assert(sqrt(vector{4., 9., 16.}) == vector{2., 3., 4.}, "sqrt");

static_assert(abs(vector{-1, -2, 3}) == vector{1, 2, 3}, "abs");

static_assert(abs(vector{{{-3., 4.}}}) == vector{5.}, "abs");

static_assert(sum(vector{1, 2, 3}) == 6, "sum");

static_assert(min(vector{1, 2, 3}) == 1, "min");

static_assert(max(vector{1, 2, 3}) == 3, "max");

static_assert(min_index(vector{1, 2, 3}) == 0, "min_index");

static_assert(max_index(vector{1, 2, 3}) == 2, "max_index");

static_assert(iota<5>(0) == vector{0, 1, 2, 3, 4}, "iota");

static_assert(iota<5, double>() == vector{0., 1., 2., 3., 4.}, "iota");

static_assert(cast<double>(vector{0, 1, 2}) == vector{0., 1., 2.}, "cast");

static_assert(linspace<4>(1.f, 4.f) == vector{1.f, 2.f, 3.f, 4.f}, "linspace");

static_assert(fill<4>(2.) == vector{2., 2., 2., 2.}, "fill");

static_assert(generate<4>([](auto i) { return double(i * i); }) ==
                  vector{0., 1., 4., 9.},
              "generate");

static_assert(vector{2, 3, 1} == rotate(vector{1, 2, 3}, 1), "rotate left");

static_assert(vector{3, 1, 2} == rotate(vector{1, 2, 3}, -1), "rotate right");

static_assert(vector{1, 2, 3} == slice<3>(vector{1, 2, 3, 4}),
              "slice-no offset");

static_assert(vector{2, 3, 4} == slice<3>(vector{1, 2, 3, 4}, 1),
              "slice with offset");

static_assert(vector{1, 2, 3, 4} == concat(vector{1, 2}, vector{3, 4}),
              "concat");

static_assert(real(vector{{{-1., 2.}, {1., -2.}}}) == vector{-1., 1.}, "real");

static_assert(imag(vector{{{-1., 2.}, {1., -2.}}}) == vector{2., -2.}, "imag");

} // namespace test
} // namespace cotila

#endif // COTILA_VECTOR_TEST_H_
