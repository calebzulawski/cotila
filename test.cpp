#include "level1.h"
#include <iostream>

int main() {
  constexpr auto v1 = 2 * cotila::make_vector(2, 3, 1) * 2;
  constexpr cotila::vector<int, 3> v2(2, 3, 3);
  constexpr int r = dot(v1, v2);
  std::cout << r << std::endl;
}
