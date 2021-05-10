#include "Horloge.hpp"

Horloge::Horloge() {
    m_Attente = false;
    m_Arret = true;
}

Horloge::~Horloge() {

}

void Horloge::lancer() {
    if(m_Arret && !m_Attente) {
        m_Debut = std::chrono::system_clock::now();
        m_Arret = false;
    } else {
        std::cout << "Erreur lancer." << std::endl;
    }
    
}

void Horloge::pause() {
    if(!m_Arret && !m_Attente) {
        m_Pause = std::chrono::system_clock::now();
        m_TempsSec = m_Pause - m_Debut;
        m_Attente = true;
    } else {
        std::cout << "Erreur pause" << std::endl;
    }

    if(!m_Arret && m_Attente){
        m_Reprendre = std::chrono::system_clock::now();
        m_TempsPause.push_back(m_Reprendre - m_Pause);
        m_Attente = false;
    } else{
        std::cout << "Erreur reprendre" << std::endl;
  }
}


void Horloge::arreter() {
    if(!m_Attente && !m_Arret) {
        m_Fin = std::chrono::system_clock::now();
        m_Attente = false;
        m_Arret = true;

        m_TempsSec = m_Fin - m_Debut;
        for(size_t i = 0; i < m_TempsPause.size(); i++) {
            m_TempsSec -= m_TempsPause[i];
        }
        m_TempsPause.clear();
    } else {
        std::cout << "Erreur arret" << std::endl;
    }
}

std::chrono::duration<double> Horloge::getTempsSec() {
    if(!m_Attente) {
        return m_TempsSec;
    } else {
        std::cout << "erreur getTempsSec\n";
        return std::chrono::steady_clock::duration::zero();
    }
}

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