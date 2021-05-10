#include "-I/usr/include/Bureau/L3/S6/Projet_git/in608-tcp_ip_simulation/src/lib/horloge/Horloge.hpp"

void test1() {
  Horloge chrono1, chrono2;
  chrono1.lancer();
  chrono1.arreter();
  std::cout << "temps d'execution chrono1 : " << chrono1.getTempsSec().count() << std::endl;
  chrono2.lancer();
  chrono2.arreter();
  std::cout << "temps d'execution chrono2 : " << chrono2.getTempsSec().count() << std::endl;
}

void test2() {
  Horloge chrono1;
  chrono1.lancer();
  chrono1.pause();
  std::cout << "temps d'execution chrono1 a la pause : " << chrono1.getTempsSec().count() << std::endl;
  chrono1.pause();
  chrono1.arreter();
  std::cout << "temps d'execution chrono2 arreter : " << chrono1.getTempsSec().count() << std::endl;
}


int main(void) {

    std::cout << "test1:" << std::endl;
    test1();
    std::cout << std::endl;
    std::cout << "test2:" << std::endl;
    test2();
    std::cout << "\nhello there" << std::endl; 
    return 0;
}