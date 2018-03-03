#ifndef COTILA_MATRIX_TEST_H_
#define COTILA_MATRIX_TEST_H_

#include <complex>
#include <cotila/cotila.h>

namespace cotila {
namespace test {

constexpr matrix<double, 3, 3> m1 = {
    {{1., 2., 3.}, 
     {4., 5., 6.}, 
     {7., 8., 9.}}};

constexpr matrix<std::complex<double>, 3, 3> m1c = {
    {{{1., 1.}, {2., 0.}, {3., 0.}},
     {{4., 1.}, {5., 0.}, {6., 0.}},
     {{7., 1.}, {8., 0.}, {9., 0.}}}};

static_assert(m1[0][2] == 3, "matrix[]");

static_assert(m1.row(2) == make_vector(7., 8., 9.), "matrix row");

static_assert(m1.column(2) == make_vector(3., 6., 9.), "matrix column");

static_assert(cast<float>(m1) ==
                  matrix<float, 3, 3>{
                      {{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}, {7.f, 8.f, 9.f}}},
              "matrix cast");

static_assert(fill<2, 2>(3.) == matrix<double, 2, 2>{{{3., 3}, {3., 3.}}},
              "matrix fill");

static_assert(transpose(m1) ==
                  matrix<double, 3, 3>{
                      {{1., 4., 7.}, {2., 5., 8.}, {3., 6., 9.}}},
              "transpose");

static_assert(hermitian(m1) ==
                  matrix<double, 3, 3>{
                      {{1., 4., 7.}, 
                       {2., 5., 8.}, 
                       {3., 6., 9.}}},
              "herm-real");

static_assert(hermitian(m1c) ==
                  matrix<std::complex<double>, 3, 3>{
                      {{{1., -1}, {4., -1.}, {7., -1.}},
                       {{2., 0.}, {5., 0.}, {8., 0.}},
                       {{3., 0.}, {6., 0.}, {9., 0.}}}},
              "herm-complex");

static_assert(matmul(m1,m1) ==
                  matrix<double, 3, 3>{
                      {{30., 36., 42.}, 
                       {66., 81., 96.}, 
                       {102., 126., 150.}}},
              "real matrix multiply");

} // namespace test
} // namespace cotila

#endif // COTILA_MATRIX_TEST_H_
