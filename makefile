.PHONY: test docs packages clean

test:
	make -C test test

docs:
	doxygen

packages:
	$(eval COTILA_VER=$(shell git describe --tags))
	echo $(COTILA_VER)
	tar jcvf /tmp/cotila-$(COTILA_VER).tar.bz2 *
	zip -r9 /tmp/cotila-$(COTILA_VER).zip *
	mkdir -p packages
	mv /tmp/cotila-$(COTILA_VER).zip packages/
	mv /tmp/cotila-$(COTILA_VER).tar.bz2 packages/

clean:
	make -C test clean
	rm -rf docs
	rm -rf packages
