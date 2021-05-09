FILES = test/Mickael.cpp src/lib/protocole_tcp_ip/internet/Internet.cpp src/lib/protocole_tcp_ip/physique/Physique.cpp src/lib/protocole_tcp_ip/transport/Transport.cpp src/lib/reseau_graphe/machine/Commutateur.cpp src/lib/reseau_graphe/machine/Machine.cpp src/lib/reseau_graphe/machine/Ordinateur.cpp src/lib/reseau_graphe/machine/Routeur.cpp

all:
	mkdir -p build
	cd build; cmake ..; make; ./Interface

Mickael:
	mkdir -p target/
	g++ -std=c++17 -Wall -Wextra -g3 $(FILES) -o test/Mickael

clean:
	@rm -Rf build/ target/
