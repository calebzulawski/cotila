.PHONY: test clean

test:
	make -C test test

doc:
	doxygen

clean:
	make -C test clean
	rm -rf doc
