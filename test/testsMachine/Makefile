CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g3 -O2
FILES = ../../src/lib/protocole_tcp_ip/**/*.cpp ../../src/lib/reseau_graphe/machine/*.cpp ../../src/lib/reseau_graphe/ospf/*.cpp

all:
	$(CC) $(CFLAGS) $(FILES) -o test

clean:
	@rm -Rf test
