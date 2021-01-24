add_executable(cotila_test test.cpp)
if (MSVC)
    target_compile_options(cotila_test PRIVATE /W4 /WX)
else ()
    target_compile_options(cotila_test PRIVATE -Werror -Wall -Wextra -pedantic -Wno-missing-braces)
endif()
target_link_libraries(cotila_test cotila::cotila)
add_test(NAME cotila_test COMMAND cotila_test)

