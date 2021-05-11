#include <iostream>

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

void Routeur::envoyer(Routeur& dest, PaquetOSPF& ospf) {
    dest.recevoir(ospf);
}

void Routeur::recevoir(PaquetOSPF& ospf) {
    m_FilePaquetsOSPF.emplace(ospf);
}

void Routeur::traitement(std::stack<std::bitset<16>> &trame, MAC nouvelleDest) {
    // Recuperation du paquet.
    Physique couchePhy;

    // Recuperation adresse MAC destination.
    std::bitset<16> macDestBA, macDestBD, macDestFE;
    macDestFE = trame.top();
    trame.pop();
    macDestBD = trame.top();
    trame.pop();
    macDestBA = trame.top();
    trame.pop();
    MAC ancienneDest = couchePhy.convertir(macDestBA, macDestBD, macDestFE);

    // Desencapsule la MAC Source d'origine qui ne nous interesse plus.
    for(int i = 0; i < 3; ++i){
        trame.pop();
    }

    // Changement adresse MAC.
    couchePhy.setMacSrc(ancienneDest);
    couchePhy.setMacDest(nouvelleDest);
    couchePhy.encapsuler(trame);
}

void Routeur::traitementPaquetOSPF() {
    PaquetOSPF &paquet = dynamic_cast<PaquetOSPF&>(m_FilePaquetsOSPF.front());

    switch (paquet.getType()) {
        case 1:
            traitementPaquetHello(dynamic_cast<PaquetHello&>(paquet));
            break;
        case 2:
            traitementPaquetDBD(dynamic_cast<PaquetDBD&>(paquet));
            break;
        case 3:
            traitementPaquetLSR(dynamic_cast<PaquetLSR&>(paquet));
            break;
        case 4:
            traitementPaquetLSU(dynamic_cast<PaquetLSU&>(paquet));
            break;
        case 5:
            traitementPaquetLSAck(dynamic_cast<PaquetLSAck&>(paquet));
            break;
        default:
            std::cout << "Type de PaquetOSPF inconnu\n";
            return;
    }
}

// Methodes privees
void Routeur::traitementPaquetHello(const PaquetHello& hello) {
    if (hello.getIdVoisin() != m_IdRouteur) {
        return;
    }

    for (auto iter = m_TableRoutage.begin(); iter != m_TableRoutage.end(); iter++) {
        auto routeur = iter->first;

        if (routeur->getIdRouteur() == hello.getIdRouteur()) {
            return;
        }
    }

    for (auto iter: m_Voisins) {
        auto machine = dynamic_cast<Routeur*>(iter);

        if (machine->getIdRouteur() == hello.getIdRouteur()) {
            PaquetHello reponse(hello.getIdRouteur());
            reponse.setEntete(Hello, m_IdRouteur);
            envoyer(*machine, reponse);
        }
    }

    exit(1);
}

void Routeur::traitementPaquetDBD(const PaquetDBD& dbd) {
    // TODO : A faire
}

void Routeur::traitementPaquetLSR(const PaquetLSR& lsr) {
    // TODO : A faire
}

void Routeur::traitementPaquetLSU(const PaquetLSU& lsu) {
    // TODO : A faire
}

void Routeur::traitementPaquetLSAck(const PaquetLSAck& ack) {
    // TODO : A faire
}
