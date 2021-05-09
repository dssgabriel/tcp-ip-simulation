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
    m_SousReseau.push_back(sousReseau);
}

void Machine::setVoisin(Machine& voisin) {
    m_Voisins.push_back(&voisin);
}

void Machine::setDonnee(std::stack<std::bitset<16>>* donnee) {
    m_FileDonnees.push(donnee);
}

const std::queue<std::stack<std::bitset<16>>*>& Machine::getDonnees() {
    return m_FileDonnees;
}

std::stack<std::bitset<16>>* Machine::suppDonnee() {
    std::stack<std::bitset<16>>* donnee = m_FileDonnees.front();
    m_FileDonnees.pop();
    return donnee;
}
// Fin getters et setters

// Overloading
std::ostream& operator<<(std::ostream& flux, const Machine& m) {
    flux << "Numero : " << m.getIdMachine() << "/" << m.getNbMachine() << "\n";
    flux << "Nom : " << m.getNom() << "\n";
    IPv4 tmp = m.getIp();
    flux << "Ip : " << tmp.a.to_ulong() << "." << tmp.b.to_ulong() << ".";
    flux << tmp.c.to_ulong() << "." << tmp.d.to_ulong() << "\n";
    tmp = m.getMasque();
    flux << "Masque : " << tmp.a.to_ulong() << "." << tmp.b.to_ulong();
    flux << "." << tmp.c.to_ulong() << "." << tmp.d.to_ulong() << "\n";
    MAC tmp2;
    tmp2 = m.getMac();
    flux << "Mac : " << std::hex << tmp2.a.to_ulong() << ":";
    flux << tmp2.b.to_ulong() << ":" << tmp2.c.to_ulong() << ":";
    flux << tmp2.d.to_ulong() << ":" << tmp2.e.to_ulong() << ":" << tmp2.f.to_ulong() << "\n";

    return flux;
}