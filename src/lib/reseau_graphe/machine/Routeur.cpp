#include <cstdlib>
#include <string>
#include <utility>

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

// TODO: A refaire
/*
std::vector<Routeur> Routeur::getRouteursVoisins() {
    std::vector<Routeur> voisins;

    for (auto iter: m_Voisins) {
        auto routeur = dynamic_cast<Routeur*>(iter);

        if (routeur) {
            voisins.emplace_back(routeur);
        }
    }

    return voisins;
}
*/

// TODO: A refaire
/*
const std::vector<Liaison> Routeur::getPlusCourtChemin(Routeur& dest) {
    std::vector<Liaison> chemin;

    for (auto iter: m_TableRoutage) {
        if (iter.first->getIdRouteur() != dest.getIdRouteur()) {
            chemin.emplace_back(iter.second);
            break;
        }
    }

    return chemin;
}
*/

// Methodes
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
//     m_FilePaquetsOSPF.emplace(ospf);
}

void Routeur::traitement(std::stack<std::bitset<16>> &trame, MAC nouvelleDest) {
    // Recuperation du paquet.
    Physique couchePhy;

    // Recuperation adresse MAC destination.
    std::bitset<16> macDestBA, macDestDC, macDestFE;
    macDestFE = trame.top();
    trame.pop();
    macDestDC = trame.top();
    trame.pop();
    macDestBA = trame.top();
    trame.pop();

    // Desencapsule la MAC Source d'origine qui ne nous interesse plus.
    for (size_t i = 0; i < 3; ++i) {
        trame.pop();
    }

    // Changement adresse MAC.
    // La destination devient la source.
    trame.push(macDestBA);
    trame.push(macDestDC);
    trame.push(macDestFE);

    // Ajout nouvelle destination
    std::bitset<48> nouvelleDestBit = couchePhy.convertir(nouvelleDest);
    macDestBA = macDestDC = macDestFE = 0;
    diviser(nouvelleDestBit, macDestFE, macDestDC, macDestBA);
    trame.push(macDestBA);
    trame.push(macDestDC);
    trame.push(macDestFE);
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
    // Si l'identifiant du voisin ne correspond pas avec l'identifiant
    // du routeur, le paquet ne nous est pas destine
    if (hello.getIdVoisin() != m_IdRouteur) {
        return;
    }

    // On parcourt la table de routage pour verifier si le routeur nous
    // envoyant le paquet Hello est connu
    for (auto iter: m_TableRoutage) {
        // Si le routeur est connu, alors on lui envoie un paquet DBD
        if (iter.first->getIdRouteur() == hello.getIdRouteur()) {
            std::vector<LSA> annonces;

            // On initialise la liste des annonces LSA
            for (auto routeur: m_TableRoutage) {
                LSA lsa(routeur.first->getIdRouteur(),
                        routeur.first->getIdRouteur(),
                        routeur.first->getSousReseau()
                );
                annonces.emplace_back(lsa);
            }

            // On envoie un paquet DBD au routeur nous envoyant le paquet Hello
            auto destinataire = iter.first;

            PaquetDBD reponse(annonces);
            reponse.setEntete(DBD, m_IdRouteur);
            envoyer(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

            return;
        }
    }
}

void Routeur::traitementPaquetDBD(PaquetDBD& dbd) {
    auto annonces = dbd.getAnnoncesLSA();
    std::vector<std::bitset<32>> idADemander;

    for (auto annonce: annonces) {
        for (auto iter: m_TableRoutage) {
            auto routeur = iter.first;

            if (annonce.getIdRouteur() != routeur->getIdRouteur()) {
                bool trouve = false;

                for (auto verif: m_TableRoutage) {
                    if (verif.first->getIdRouteur() ==
                        routeur->getIdRouteur())
                    {
                        trouve = true;
                        break;
                    }
                }

                if (!trouve) {
                    idADemander.emplace_back(annonce.getIdLSA());
                    m_TableLSADemandes.emplace(*routeur, annonce.getIdLSA());
                }
            }
        }
    }

    if (!idADemander.empty()) {
        for (auto iter: m_TableRoutage) {
            if (iter.first->getIdRouteur() == dbd.getIdRouteur()) {
                auto destinataire = iter.first;

                PaquetLSR reponse(dbd.getIdRouteur(), idADemander);
                reponse.setEntete(LSR, m_IdRouteur);
                envoyer(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

                return;
            }
        }
    }
}

void Routeur::traitementPaquetLSR(PaquetLSR& lsr) {
    if (lsr.getIdAnnonceur() != m_IdRouteur) {
        // Le paquet LSR ne nous est pas destine,
        // on sort directement de la methode
        return;
    }

    auto vec = lsr.getIdLSADemandes();
    std::vector<LSA> annoncesDemandes;

    for (auto id: vec) {
        for (auto iter: m_TableRoutage) {
            auto routeur = iter.first;

            if (routeur->getIdRouteur() == (uint8_t)(id.to_ulong())) {
                LSA lsa(routeur->getIdRouteur(),
                        routeur->getIdRouteur(),
                        routeur->getSousReseau()
                );
                annoncesDemandes.emplace_back(lsa);
            }
        }
    }

    for (auto iter: m_TableRoutage) {
        if (lsr.getIdRouteur() == iter.first->getIdRouteur()) {
            auto destinataire = iter.first;

            for (auto annonce: annoncesDemandes) {
                m_TableLSAEnvoyes.emplace(*destinataire, annonce.getIdLSA());
            }

            PaquetLSU reponse(annoncesDemandes);
            reponse.setEntete(LSU, m_IdRouteur);
            envoyer(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

            return;
        }
    }
}

void Routeur::traitementPaquetLSU(const PaquetLSU& lsu) {
    // TODO : A faire
}

void Routeur::traitementPaquetLSAck(const PaquetLSAck& ack) {
    // TODO : A faire
}
