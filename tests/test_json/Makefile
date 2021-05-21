CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g3 -O2

OSPF = ../../src/lib/reseau_graphe/ospf/*.cpp
FICHIER = ../../src/lib/gestion_fichiers/*.cpp
MACHINE = ../../src/lib/reseau_graphe/machine/*.cpp
PROTOCOLE = ../../src/lib/protocole_tcp_ip/**/*.cpp
RESEAU = ../../src/lib/reseau_graphe/ReseauGraphe.cpp

FILES = $(OSPF) $(FICHIER) $(MACHINE) $(PROTOCOLE) $(RESEAU)

all:
	$(CC) $(CFLAGS) $(FILES) Json.cpp -o ../test/testsJson/test
	./test