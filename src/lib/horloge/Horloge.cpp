/**

 * @file        Horloge.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe Horloge.
 * 
 * @author      Florian CAMBRESY
 * @date        2021

 **/
 
 #include "Horloge.hpp"


 /**
  * @brief Constructeur de la classe Horloge.
  * 
  **/
Horloge::Horloge() : m_Attente(false), m_Arret(true) {
    m_TempsSec = std::chrono::steady_clock::duration::zero();
}

 /**
  * @brief Destructeur de la classe Horloge.
  *
  **/
Horloge::~Horloge() {

}


 /**
  * @brief Permet de lancer un chronomètre via l'horloge interne de l'ordinateur.
  * 
  * @return void.
  **/
void Horloge::lancer() {
    if (m_Arret && !m_Attente) {
        m_Debut = std::chrono::system_clock::now();
        m_Arret = false;
    } else if (!m_Arret && m_Attente) {
        m_Reprendre = std::chrono::system_clock::now();
        m_TempsPause.push_back(m_Reprendre - m_Pause);
        m_Attente = false;
    } else {
        std::cout << "ERREUR" << std::endl;
    }

}

 /**
  * @brief Permet de sauvegarder les moments de pauses.
  * 
  * @return void.
  **/
void Horloge::pause() {
    if (!m_Arret && !m_Attente) {
        m_Pause = std::chrono::system_clock::now();
        m_TempsSec = m_Pause - m_Debut;
        m_Attente = true;
    } else {
        std::cout << "Erreur pause" << std::endl;
    }
}

/**
  * @brief Permet d'arreter l'horloge.
  * 
  * @return void.
  **/
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

void Horloge::remettreAZero() {
    m_TempsSec = std::chrono::steady_clock::duration::zero();
    m_TempsPause.clear();
}

/**
  * @brief Getter pour l'argument m_TempsSec.
  * 
  * @return std::chrone::duration<duration>.
  **/
std::chrono::duration<double> Horloge::getTempsSec() {
    if (!m_Attente) {
        if (m_TempsSec != std::chrono::steady_clock::duration::zero()) {
            return m_TempsSec;
        }
        auto tmp = std::chrono::system_clock::now();
        return tmp - m_Debut;    
    } else {
        std::cout << "erreur getTempsSec\n";
        return std::chrono::steady_clock::duration::zero();
    }
}