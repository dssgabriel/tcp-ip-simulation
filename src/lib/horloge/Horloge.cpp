#include "Horloge.hpp"

Horloge::Horloge() :
    m_Attente(false),
    m_Arret(true)
{
}

Horloge::~Horloge() {

}

void Horloge::lancer() {
    if (m_Arret && !m_Attente) {
        m_Debut = std::chrono::system_clock::now();
        m_Arret = false;
    } else {
        std::cout << "Erreur lancer." << std::endl;
    }

}

void Horloge::pause() {
    if (!m_Arret && !m_Attente) {
        m_Pause = std::chrono::system_clock::now();
        m_TempsSec = m_Pause - m_Debut;
        m_Attente = true;
    } else {
        std::cout << "Erreur pause" << std::endl;
    }

    if (!m_Arret && m_Attente) {
        m_Reprendre = std::chrono::system_clock::now();
        m_TempsPause.push_back(m_Reprendre - m_Pause);
        m_Attente = false;
    } else {
        std::cout << "Erreur reprendre" << std::endl;
  }
}


void Horloge::arreter() {
    if (!m_Attente && !m_Arret) {
        m_Fin = std::chrono::system_clock::now();
        m_Attente = false;
        m_Arret = true;

        m_TempsSec = m_Fin - m_Debut;
        for (size_t i = 0; i < m_TempsPause.size(); i++) {
            m_TempsSec -= m_TempsPause[i];
        }
        m_TempsPause.clear();
    } else {
        std::cout << "Erreur arret" << std::endl;
    }
}

std::chrono::duration<double> Horloge::getTempsSec() {
    if (!m_Attente) {
        return m_TempsSec;
    } else {
        std::cout << "erreur getTempsSec\n";
        return std::chrono::steady_clock::duration::zero();
    }
}
