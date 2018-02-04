#ifndef COTILA_LEVEL1_TEST_H_
#define COTILA_LEVEL1_TEST_H_

#include "level1.h"

namespace cotila {

static_assert(make_vector(1, 2, 3) == make_vector(1, 2, 3), "operator==");

static_assert(make_vector(1, 2, 3) != make_vector(3, 2, 1), "operator!=");

static_assert(2 + make_vector(1, 2, 3) == make_vector(3, 4, 5), "operator+");

static_assert(make_vector(1, 2, 3) + 2 == make_vector(3, 4, 5), "operator+");

static_assert(make_vector(1, 2, 3) + make_vector(1, 2, 3) ==
                  make_vector(2, 4, 6),
              "operator+");

} // namespace cotila

#endif // COTILA_LEVEL1_TEST_H_
