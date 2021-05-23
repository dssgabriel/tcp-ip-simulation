CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g3 -O2 #-fopenmp

COMMUN = ../../src/include/Commun.cpp
RESEAU = ../../src/lib/reseau_graphe/**/*.cpp ../../src/lib/reseau_graphe/*.cpp
FICHIER = ../../src/lib/gestion_fichiers/*.cpp
PROTOCOLE = ../../src/lib/protocole_tcp_ip/**/*.cpp
TEST = *.cpp

FILES = $(TEST) $(COMMUN) $(FICHIER) $(PROTOCOLE) $(RESEAU)

all:
	$(CC) $(CFLAGS) $(FILES) -o test
	./test

clean:
	@rm -Rf test
