all:
	@mkdir -p build
	@cd build
	cmake ..
	make
	./Interface

clean:
	@rm -Rf build
