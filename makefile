all: 
	mkdir -p build
	cd build; cmake ..; make; ./Interface

clean:
	rm -r build
