#ifndef COTILA_MATRIX_TEST_H_
#define COTILA_MATRIX_TEST_H_

#include <complex>
#include <cotila/cotila.h>

namespace cotila::test {

// Uniform initialization
constexpr matrix<double, 3, 3> m1 = {
    1., 2., 3.,
    4., 5., 6.,
    7., 8., 9.};

// Type deduction
constexpr matrix m2 = {{{1.,2.}}};

constexpr matrix m22 = {
    {{1., 3.},
     {2., 7.}}};

constexpr matrix m1c = {
    {{{1., 1.}, {2., 0.}, {3., 0.}},
     {{4., 1.}, {5., 0.}, {6., 0.}},
     {{7., 1.}, {8., 0.}, {9., 0.}}}};

static_assert(m1[0][2] == 3, "matrix[]");

static_assert(m1.row(2) == vector{7., 8., 9.}, "matrix row");

static_assert(m1.column(2) == vector{3., 6., 9.}, "matrix column");

static_assert(as_row(m1.row(2)) == matrix{{{7., 8., 9.}}}, "row vector as matrix");

static_assert(as_column(m1.column(2)) == matrix{{{3.}, {6.}, {9.}}}, "column vector as matrix");

static_assert(cast<float>(m1) ==
                  matrix{{{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}, {7.f, 8.f, 9.f}}},
              "matrix cast");

static_assert(fill<2, 2>(3.) == matrix{{{3., 3.}, {3., 3.}}},
              "matrix fill");

static_assert(rotate(m1, 1) == matrix<double, 3, 3> {4, 5, 6, 7, 8, 9, 1, 2, 3}, "rotate left");

static_assert(rotate(m1, -1) == matrix<double, 3, 3> {7, 8, 9, 1, 2, 3, 4, 5, 6}, "rotate right");

static_assert(rotate(m1, -1) == rotate(m1, 2), "rotate modulo");

static_assert(transpose(m1) ==
                  matrix{{{1., 4., 7.},
                          {2., 5., 8.},
                          {3., 6., 9.}}},
              "transpose");

static_assert(hermitian(m1) ==
                  matrix{{{1., 4., 7.},
                          {2., 5., 8.},
                          {3., 6., 9.}}},
              "herm-real");

static_assert(hermitian(m1c) ==
                  matrix{{{{1., -1.}, {4., -1.}, {7., -1.}},
                          {{2., 0.},  {5., 0.},  {8., 0.}},
                          {{3., 0.},  {6., 0.},  {9., 0.}}}},
              "herm-complex");

static_assert(matmul(m1,m1) ==
                  matrix{{{30., 36., 42.},
                          {66., 81., 96.},
                          {102., 126., 150.}}},
              "real matrix multiply");

static_assert(identity<double, 3> ==
                  matrix{{{1., 0., 0.},
                          {0., 1., 0.},
                          {0., 0., 1.}}},
              "identity");

static_assert(identity<std::complex<double>, 3> ==
                  matrix<std::complex<double>, 3, 3>{
                         {{1., 0., 0.},
                          {0., 1., 0.},
                          {0., 0., 1.}}},
              "complex identity");

static_assert(repmat<3, 2>(m2) ==
                  matrix{
                      {{1., 2., 1., 2.},
                       {1., 2., 1., 2.},
                       {1., 2., 1., 2.}}},
              "repmat");

static_assert(kron(m2, m2) ==
                matrix{{{1., 2., 2., 4.}}},
              "kron");

static_assert(identity<double, 3> == inverse(identity<double, 3>), "inverse-identity");

static_assert(inverse(m22) ==
                matrix{
                {{ 7., -3.},
                 {-2.,  1.}}},
              "inverse");

static_assert(matmul(inverse(m22), matrix<double, 2, 1>{{{1.},{1.}}}) ==
                matrix{{{4.}, {-1.}}},
                "A^-1*b = x");

static_assert(trace(m1) == 15, "matrix trace");

static_assert(horzcat(identity<double, 2>, identity<double, 2>) ==
                matrix<double, 2, 4>{{{1., 0., 1., 0.}, {0., 1., 0., 1.}}}, "horzcat");

static_assert(vertcat(identity<double, 2>, identity<double, 2>) ==
                matrix<double, 4, 2>{{{1., 0.}, {0., 1.}, {1., 0.}, {0., 1.}}}, "vertcat");

static_assert(submat<2, 2>(m1, 1, 1) == matrix{{{5., 6.}, {8., 9.}}}, "submat");

static_assert(macs(m1) == 18, "maximum absolute value column sum norm");

static_assert(mars(m1) == 24, "maximum absolute value row sum norm");

static_assert(rref(m1) ==
                matrix{
                {{1., 0., -1.},
                 {0., 1., 2.},
                 {0., 0., 0.}}},
                "rref");

static_assert(rank(m1) == 2, "rank");

static_assert(det(m1) == 0, "det");

static_assert(det(m22) == 1, "det");

static_assert(reshape<1, 9>(m1) == matrix<double, 1, 9>{
        {{1., 2., 3., 4., 5., 6., 7., 8., 9.}}}, "reshape");

static_assert(
    reshape<4, 2>(matrix<double, 2, 4>{{{1., 2., 3., 4.}, {5., 6., 7., 8.}}}) ==
        matrix<double, 4, 2>{{{1., 2.}, {3., 4.}, {5., 6.}, {7., 8.}}},
    "reshape");

static_assert(real(m1c) == m1, "real");

static_assert(imag(m1c) == matrix{{{1., 0., 0.},
                                   {1., 0., 0.},
                                   {1., 0., 0.}}}, "imag");

} // namespace cotila

#endif // COTILA_MATRIX_TEST_H_
