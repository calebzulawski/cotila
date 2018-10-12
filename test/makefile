INCLUDES=../include
CFLAGS=-I$(INCLUDES) -std=c++17 -Werror -Wall -Wextra -Wpedantic -Wno-missing-braces

test: test.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f test
