#include "Contexte.h"

// Constructeur //
Contexte::Contexte()
{
    // Création de l'arbre
    //m_Reseau = new ReseauGraphe();
    m_TabCongestion = new std::vector<ElementControleCongestion>();
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
    numConfig = 2;
    int a = 3;
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
