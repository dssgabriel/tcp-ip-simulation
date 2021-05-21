CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g3 -O2

COMMUN = ../../src/include/Commun.cpp
OSPF = ../../src/lib/reseau_graphe/ospf/*.cpp
MACHINE = ../../src/lib/reseau_graphe/machine/*.cpp
FICHIER = ../../src/lib/gestion_fichiers/*.cpp
PROTOCOLE = ../../src/lib/protocole_tcp_ip/**/*.cpp
RESEAU = ../../src/lib/reseau_graphe/ReseauGraphe.cpp

FILES = $(COMMUN) $(OSPF) $(FICHIER) $(MACHINE) $(PROTOCOLE) $(RESEAU)

all:
	$(CC) $(CFLAGS) $(FILES) TestMachine.cpp -o test
	./test

clean:
	@rm -Rf test
