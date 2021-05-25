/**

 * @file        Horloge.hpp
 * @brief       Déclaration de la classe Horloge.
 *
 * @author      Florian CAMBRESY
 * @date        2021

 **/
 #pragma once

#include <vector>
#include <chrono>
#include <iostream>

class Horloge {
    private:
        // Attributs
        std::chrono::time_point<std::chrono::system_clock> m_Debut;
        std::chrono::time_point<std::chrono::system_clock> m_Fin;
        std::chrono::time_point<std::chrono::system_clock> m_Pause;
        
        std::chrono::time_point<std::chrono::system_clock>
            m_Reprendre;

        std::vector<std::chrono::duration<double>> m_TempsPause;
        std::chrono::duration<double> m_TempsSec;

        bool m_Attente, m_Arret;

    public:
        // Constructeur
        Horloge();

        // Destructeur
        ~Horloge();
    
        // Getter
        std::chrono::duration<double> getTempsSec();
    
        // Methodes publiques
        void lancer();
        void pause();
        void arreter();
        void remettreAZero();
};