#include "ReseauGraphe.hpp"

ReseauGraphe::ReseauGraphe() :
    m_Machines(nullptr),
    m_Liaisons(nullptr)
{
}

ReseauGraphe::~ReseauGraphe() {
}

// Getters & setters
void setNom(const std::string nom) {
    m_Nom = nom;
}

std::string& ReseauGraphe::getNom() {
    return m_Nom;
}

Machine& ReseauGraphe::getMachine(const IPv4& ip) {
    return ip;
}

// Methodes
bool ReseauGraphe::estConnexe() {

}

void ReseauGraphe::ajouter(Machine m) {
    m_Machines.emplace_back(m);
}

void ReseauGraphe::ajouter(Liaison l) {
    m_Liaisons.emplace_back(l);
}

void ReseauGraphe::routageDynamique() {
}