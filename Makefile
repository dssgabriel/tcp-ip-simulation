# TEST MACHINE #
TCP_IP=$(shell find src/lib/protocole_tcp_ip/ -type f -iname '*.cpp')
MACHINE=src/lib/reseau_graphe/machine/*.cpp
TEST_MACHINE=test/testMachine.cpp $(TCP_IP) $(MACHINE)
# TEST MACHINE #

# APPLICATION #
all:
	mkdir -p build
	cd build; cmake ..; make; ./Interface

clean:
	@rm -Rf build/ target/
# APPLICATION #

# TEST MACHINE #
machine:
	mkdir -p target/
	g++ -std=c++17 -Wall -Wextra -g3 $(TEST_MACHINE) -o test/testMachine

cleanTarget:
	rm target/*.o

cleanMachine: cleanTarget
	rm test/machine
# TEST MACHINE #

# TEST JSON #
json:
	g++ -std=c++17 -Wall -Wextra -g3 test/testJson.cpp -o test/testJson
	./test/testJson
# TEST JSON #