#include "Machine.hpp"

IPv4 ipZero = {
    .a = std::bitset<8>(0),
    .b = std::bitset<8>(0),
    .c = std::bitset<8>(0),
    .d = std::bitset<8>(0)
};

IPv4 ipMax = {
    .a = std::bitset<8>(255),
    .b = std::bitset<8>(255),
    .c = std::bitset<8>(255),
    .d = std::bitset<8>(255)
};

MAC macZero = {
    .a = std::bitset<8>(0),
    .b = std::bitset<8>(0),
    .c = std::bitset<8>(0),
    .d = std::bitset<8>(0),
    .e = std::bitset<8>(0),
    .f = std::bitset<8>(0)
};

MAC macMax = {
    .a = std::bitset<8>(255),
    .b = std::bitset<8>(255),
    .c = std::bitset<8>(255),
    .d = std::bitset<8>(255),
    .e = std::bitset<8>(255),
    .f = std::bitset<8>(255)
};

uint16_t Machine::m_NbMachine = 0;

// Constructeur
Machine::Machine() {
    m_NbMachine++;
    m_IdMachine = m_NbMachine;
    
    m_Nom = "Machine" + std::to_string(m_IdMachine);

    m_Ip = ipZero;
    m_Mac = macZero;
    m_Masque = ipZero;
    m_SousReseau.clear();

    m_Voisins.clear();
    
    while(!m_FileDonnees.empty()) {
        m_FileDonnees.pop();
    }
}

// Getters & setters
const uint16_t& Machine::getNbMachine() const {
    return m_NbMachine;
}

const uint16_t& Machine::getIdMachine() const {
    return m_IdMachine;
}

void Machine::setNom(const std::string& nom) {
    m_Nom = nom; 
}

const std::string& Machine::getNom() const {
    return m_Nom;
}

void Machine::setIp(const IPv4& ip) {
    m_Ip = ip;
}

const IPv4& Machine::getIp() const {
    return m_Ip;
}

void Machine::setMasque(const IPv4& masque) {
    m_Masque = masque;
}

const IPv4& Machine::getMasque() const {
    return m_Masque;
}

void Machine::setMac(const MAC& mac) {
    m_Mac = mac;
}

const MAC& Machine::getMac() const {
    return m_Mac;
}

void Machine::setSousReseau(const IPv4& sousReseau) {
    m_SousReseau.emplace_back(sousReseau);
}

const std::vector<IPv4>& Machine::getSousReseau() const {
    return m_SousReseau;
}

void Machine::setVoisin(Machine& voisin) {
    m_Voisins.emplace_back(&voisin);
}

Machine* Machine::getVoisin(MAC adresseVoisin) {
    for(size_t i = 0; i < m_Voisins.size(); ++i) {
        if(m_Voisins[i]->getMac() == adresseVoisin) {
            return m_Voisins[i];
        }
    }

    return nullptr;
}

void Machine::setDonnee(const std::stack<std::bitset<16>>& trame) {
    m_FileDonnees.emplace(trame);
}

const std::queue<std::stack<std::bitset<16>>>& Machine::getDonnees() {
    return m_FileDonnees;
}

std::stack<std::bitset<16>> Machine::suppDonnee() {
    std::stack<std::bitset<16>> donnee = m_FileDonnees.front();
    m_FileDonnees.pop();
    return donnee;
}
// Fin getters et setters

// Overloading
std::ostream& operator<<(std::ostream& flux, const Machine& m) {
    flux << "Numero : " << m.getIdMachine() << "/" << m.getNbMachine() << std::endl;
    flux << "Nom : " << m.getNom() << std::endl;
    flux << "Ip : " << m.getIp() << std::endl;
    flux << "Masque : " << m.getMasque() << std::endl;
    flux << "Mac : " << m.getMac() << std::endl;

    flux << "Liste des sous réseaux : \n";
    std::vector<IPv4> cpySousReseau = m.getSousReseau();
    for(IPv4 sousReseau : cpySousReseau) {
        flux << "\t > " << sousReseau << std::endl;
    }

    return flux;
}