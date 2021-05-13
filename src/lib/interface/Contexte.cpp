#include "Contexte.hpp"

// Constructeur
Contexte::Contexte() {
    // Chargement du reseau Simple par defaut
    /*m_Reseau = nullptr;
    chargerConfig(1);*/
    m_Temps = 0;
    m_TabCongestion = new std::vector<ElementControleCongestion>();
    //std::cout << m_Reseau->getNom() << "\n";
}

/*ReseauGraphe* Contexte::getReseau() {
    return m_Reseau;
}*/

ParamInterface& Contexte::getConfig() {
    return m_Config;
}

MAC& Contexte::getMACArrivee() {
    return m_Destination;
}

int64_t& Contexte::getTemps() {
    return m_Temps;
}

void Contexte::charger() {

}

void Contexte::sauvegarder() {

}

void Contexte::exporterGraphe() {

}

std::string Contexte::informationsReseau() {
    return "test";
}

void Contexte::chargerConfig(int numConfig) {
    /*if(numConfig == 1) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauSimple");
    }
    else if(numConfig == 2) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauMaison");
    }
    else if(numConfig == 3) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauPme");
    }
    else if(numConfig == 4) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauEntreprise");
    }*/
}

void Contexte::executerSimulation() {

}

void Contexte::rafraichir() {

}

void Contexte::stopSimulation() {

}

// Destructeur //
Contexte::~Contexte() {
    if(m_TabCongestion) { delete m_TabCongestion;}
}
