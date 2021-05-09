all:
	mkdir -p build
	cd build; cmake ..; make; ./Interface

Mickael:
	g++ -c -std=c++17 -Wall -Wextra -g src/bin/Mickael.cpp -o target/Mickael.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/protocole_tcp_ip/internet/Internet.cpp -o target/Internet.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/protocole_tcp_ip/physique/Physique.cpp -o target/Physique.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/protocole_tcp_ip/transport/Transport.cpp -o target/Transport.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/reseau_graphe/machine/Commutateur.cpp -o target/Commutateur.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/reseau_graphe/machine/Machine.cpp -o target/Machine.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/reseau_graphe/machine/Ordinateur.cpp -o target/Ordinateur.o
	g++ -c -std=c++17 -Wall -Wextra -g src/lib/reseau_graphe/machine/Routeur.cpp -o target/Routeur.o

	g++ target/*.o -o src/bin/Mickael

clean:
	@rm -Rf build
