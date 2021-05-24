CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g3 -O0 #-fopenmp

TEST = TestMachine.cpp
COMMUN = ../../src/include/Commun.cpp
HORLOGE = ../../src/lib/horloge/Horloge.cpp
FICHIER = ../../src/lib/gestion_fichiers/*.cpp
PROTOCOLE = ../../src/lib/protocole_tcp_ip/**/*.cpp
RESEAU = ../../src/lib/reseau_graphe/**/*.cpp ../../src/lib/reseau_graphe/*.cpp

FILES = $(TEST) $(COMMUN) $(HORLOGE) $(FICHIER) $(PROTOCOLE) $(RESEAU)

all:
	$(CC) $(CFLAGS) $(FILES) -o test
	clear
	./test

clean:
	@rm -Rf test
