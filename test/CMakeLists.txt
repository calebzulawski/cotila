add_executable(cotila_test test.cpp)
target_compile_options(cotila_test PRIVATE -Werror -Wall -Wextra -Wpedantic -Wno-missing-braces)
target_link_libraries(cotila_test cotila::cotila)
add_test(NAME cotila_test COMMAND cotila_test)

