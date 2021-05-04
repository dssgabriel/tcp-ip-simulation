#include "Routeur.hpp"

uint8_t Routeur::m_NbRouteur = 0;

// Constructeur
Routeur::Routeur() : Machine() {
    m_NbRouteur++;
    m_IdRouteur = m_NbRouteur;

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

std::vector<Routeur&>& Routeur::getRouteursVoisins() {
    // TODO : A faire
}

// Methodes
const std::vector<Liaison>& Routeur::getPlusCourtChemin(const Routeur& dest) {
    // TODO : A faire
}

void Routeur::envoyer() {
    // TODO : A faire
}

void Routeur::recevoir() {
    // TODO : A faire
}

void Routeur::traitement() {
    // TODO : A faire
}
