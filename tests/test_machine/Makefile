CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g3 -Ofast #-fopenmp

TEST = TestMachine.cpp
COMMUN = ../../src/include/Commun.cpp
FICHIER = ../../src/lib/gestion_fichiers/*.cpp
HORLOGE = ../../src/lib/horloge/Horloge.cpp
PROTOCOLE = ../../src/lib/protocole_tcp_ip/**/*.cpp
RESEAU = ../../src/lib/reseau_graphe/**/*.cpp ../../src/lib/reseau_graphe/*.cpp
TEST = *.cpp

FILES = $(COMMUN) $(FICHIER) $(HORLOGE) $(PROTOCOLE) $(RESEAU) $(TEST)

all:
	$(CC) $(CFLAGS) $(FILES) -o test

clean:
	@rm -Rf test
