#include "Routeur.hpp"

uint8_t Routeur::m_NbRouteur = 0;

// Constructeur
Routeur::Routeur() : Machine() {
    m_NbRouteur++;
    m_IdRouteur = m_NbRouteur;

    m_Nom = "Routeur" + std::to_string(m_IdRouteur);

    m_TableRoutage.clear();
    m_TableLSADemandes.clear();
    m_TableLSAEnvoyes.clear();
}

// Desctructeur
Routeur::~Routeur() {}

// Getters & setters
uint8_t Routeur::getNbRouteur() {
    return m_NbRouteur;
}

uint8_t Routeur::getIdRouteur() {
    return m_IdRouteur;
}

// std::vector<Routeur&>& Routeur::getRouteursVoisins() {
    // TODO : A faire
// }

// Methodes
// const std::vector<Liaison>& Routeur::getPlusCourtChemin(const Routeur& dest) {
    // TODO : A faire
// }

void Routeur::envoyer() {
    // TODO : A faire
}

void Routeur::recevoir() {
    // TODO : A faire
}

void Routeur::traitement(std::stack<std::bitset<16>> &trame, MAC nouvelleDest) {
    // Recuperation du paquet.
    Physique couchePhy;
    
    // Recuperation adresse MAC destination.
    std::bitset<16> macDestAB, macDestCD, macDestEF;
    macDestAB = trame.top();
    trame.pop();
    macDestCD = trame.top();
    trame.pop();
    macDestEF = trame.top();
    trame.pop();
    MAC ancienneDest = couchePhy.convertir(macDestAB, macDestCD, macDestEF);

    // Desencapsule la MAC Source d'origine qui ne nous interesse plus.
    for(int i = 0; i < 3; ++i){
        trame.pop();
    }

    // Changement adresse MAC.
    couchePhy.setMacSrc(ancienneDest);
    couchePhy.setMacDest(nouvelleDest);
    couchePhy.encapsuler(trame);
}
