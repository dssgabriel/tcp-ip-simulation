#include "../../src/lib/horloge/Horloge.hpp"

void test1() {
    Horloge chrono1, chrono2;

    chrono1.lancer();
    chrono1.arreter();
    std::cout << "Temps d'execution chrono1 : " << chrono1.getTempsSec().count() << std::endl;

    chrono2.lancer();
    chrono2.arreter();
    std::cout << "Temps d'execution chrono2 : " << chrono2.getTempsSec().count() << std::endl;
}

void test2() {
    Horloge chrono1;

    chrono1.lancer();
    chrono1.pause();
    std::cout << "Temps d'execution chrono1 a la pause : " << chrono1.getTempsSec().count() << std::endl;

    chrono1.pause();
    chrono1.arreter();
    std::cout << "Temps d'execution chrono1 arrete : " << chrono1.getTempsSec().count() << std::endl;
}


int main() {
    std::cout << "Test 1 :" << std::endl;
    test1();
    std::cout << std::endl;

    std::cout << "Test2 : " << std::endl;
    test2();
    std::cout << "\nHello there" << std::endl;

    return 0;
}
