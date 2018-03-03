.PHONY: test docs clean

test:
	make -C test test

docs:
	doxygen

clean:
	make -C test clean
	rm -rf docs
