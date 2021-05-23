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

    chrono1.lancer();
    chrono1.arreter();
    std::cout << "Temps d'execution chrono1 arrete : " << chrono1.getTempsSec().count() << std::endl;
}

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

void test3() {
    Horloge o;
    o.lancer();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    std::cout << "Tmp : " << o.getTempsSec().count() << std::endl;
    std::cout << "f(32) = " << fibonacci(42) << '\n';
    std::cout << "Tmp2 : " << o.getTempsSec().count() << std::endl;
    o.arreter();
}

int main() {
    // std::cout << "Test 1 :" << std::endl;
    // test1();
    // std::cout << std::endl;

    // std::cout << "Test2 : " << std::endl;
    // test2();
    // std::cout << "\nHello there" << std::endl;

    test3();

    return 0;
}
