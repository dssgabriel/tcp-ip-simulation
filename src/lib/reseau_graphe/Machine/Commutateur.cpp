#include "Commutateur.hpp"

uint8_t Commutateur::m_NbrCommutateur = 0;

// Constructeurs
Commutateur::Commutateur() : Machine() {}

// Destructeur
Commutateur::~Commutateur() {}

// Getters
uint8_t Commutateur::getNbrCommutateur() {
    return m_NbrCommutateur;
}

uint8_t Commutateur::getIdCommutateur() {
    return m_IdCommutateur; 
}

// Methode
void Commutateur::envoyer() {
    // TODO : A faire
}

void Commutateur::recevoir() {
    // TODO : A faire
}

void Commutateur::traitement() {
    // TODO : A faire
}

MAC Commutateur::trouverMacDest(const IPv4& ip) {
    auto trouve = m_CacheMem.find(ip);
    if(trouve != m_CacheMem.end()) {
        return trouve->second;
    }
    else {
        std::cout << "ERREUR : Aucune adresse MAC ne correspond à l'adresse IP indiqué\n";
        return macZero;
    }
}