#ifndef COTILA_SCALAR_TEST_H_
#define COTILA_SCALAR_TEST_H_

#include <complex>
#include <cotila/cotila.h>

namespace cotila {

static_assert(sqrt(625.) == 25, "sqrt");

static_assert(sqrt(625.f) == 25, "sqrt");

static_assert(exponentiate(5, 2) == 25, "exponentiate");

static_assert(nthroot(27, 3) == 3, "nth root");

static_assert(cotila::abs(std::complex(3., 4.)) == 5., "abs");

static_assert(cotila::abs(-4) == 4, "abs");

static_assert(cotila::abs(4) == 4, "abs");

static_assert(cotila::conj(4) == 4, "conj");

static_assert(cotila::conj(-4) == -4, "conj");

static_assert(cotila::conj(std::complex(3, 4)) == std::complex(3, -4), "conj");

static_assert(cotila::conj(std::complex(3, -4)) == std::complex(3, 4), "conj");

} // namespace cotila

#endif
