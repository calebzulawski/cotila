#ifndef COTILA_LEVEL1_TEST_H_
#define COTILA_LEVEL1_TEST_H_

#include <complex>
#include <cotila/level1.h>

namespace cotila {
namespace test {

using cplxf = std::complex<float>;
using cplxd = std::complex<double>;

static_assert(make_vector(1, 2, 3) == make_vector(1, 2, 3), "operator==");

static_assert(make_vector(1, 2, 3) != make_vector(3, 2, 1), "operator!=");

static_assert(2 + make_vector(1, 2, 3) == make_vector(3, 4, 5), "operator+");

static_assert(make_vector(1, 2, 3) + 2 == make_vector(3, 4, 5), "operator+");

static_assert(make_vector(1, 2, 3) + make_vector(1, 2, 3) ==
                  make_vector(2, 4, 6),
              "operator+");

static_assert(conj(make_vector(cplxf(-1, 2), cplxf(1, -2))) ==
                  make_vector(cplxf(-1, -2), cplxf(1, 2)),
              "conj");

static_assert(sqrt(make_vector(4., 9., 16.)) == make_vector(2., 3., 4.),
              "sqrt");

static_assert(abs(make_vector(-1, -2, 3)) == make_vector(1, 2, 3), "abs");

static_assert(abs(make_vector(cplxd(-3, 4))) == make_vector(5.), "abs");

static_assert(sum(make_vector(1, 2, 3)) == 6, "sum");

static_assert(min(make_vector(1, 2, 3)) == 1, "min");

static_assert(max(make_vector(1, 2, 3)) == 3, "max");

static_assert(min_index(make_vector(1, 2, 3)) == 0, "min_index");

static_assert(max_index(make_vector(1, 2, 3)) == 2, "max_index");

static_assert(iota<5>(0) == make_vector(0, 1, 2, 3, 4), "iota");

static_assert(cast<double>(make_vector(0, 1, 2)) == make_vector(0., 1., 2.),
              "cast");

static_assert(linspace<4>(1.f, 4.f) == make_vector(1.f, 2.f, 3.f, 4.f),
              "linspace");

static_assert(fill<4>(2.) == make_vector(2., 2., 2., 2.), "fill");

} // namespace test
} // namespace cotila

#endif // COTILA_LEVEL1_TEST_H_
