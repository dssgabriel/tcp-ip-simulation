Horloge: clean compile
	./Horloge

compile: Horloge.o
	g++ Horloge.o -o Horloge

Horloge.o: Horloge.cpp Horloge.hpp
	gcc -c -std=c++17 Horloge.cpp -o Horloge.o


clean :
	rm -f *.o
	rm -f Horloge
	clear