#include "vector.h"
#include <iostream>

int main() {
  constexpr cotila::Vector<int, 3> v(1, 2, 3);
  std::cout << v.get<1>() << std::endl;
}
