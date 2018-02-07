INCLUDES=../include
CFLAGS=-I$(INCLUDES) -std=c++17

test: test.cpp
	$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f test
