#include "ReseauGraphe.hpp"
#include "machine/Routeur.hpp"
#include <cstdlib>

ReseauGraphe::ReseauGraphe() {
}

ReseauGraphe::~ReseauGraphe() {
}

// Getters & setters
void ReseauGraphe::setNom(const std::string nom) {
    m_Nom = nom;
}

std::string& ReseauGraphe::getNom() {
    return m_Nom;
}

Machine& ReseauGraphe::getMachine(const IPv4& ip) {
    for (size_t i = 0; i < m_Machines.size(); i++) {
        if (m_Machines[i].getIp() == ip) {
            return m_Machines[i];
        }
    }

    exit(1);
}

Routeur& ReseauGraphe::getRouteur(const uint8_t& idRouteur) {
    for (size_t i = 0; i < m_Machines.size(); i++) {
        auto routeur = dynamic_cast<Routeur&>(m_Machines[i]);
        if (routeur.getIdRouteur() == idRouteur) {
            return dynamic_cast<Routeur&>(m_Machines[i]);
        }
    }

    exit(1);
}

// Methodes
bool ReseauGraphe::estConnexe() {
    return false;
}

void ReseauGraphe::ajouter(Machine m) {
    m_Machines.emplace_back(m);
}

void ReseauGraphe::ajouter(Liaison l) {
    m_Liaisons.emplace_back(l);
}

void ReseauGraphe::routageDynamique() {
}
