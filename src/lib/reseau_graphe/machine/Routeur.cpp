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
void Routeur::envoyer(const uint32_t) {
    // TODO : A faire
}

void Routeur::recevoir() {
    // TODO : A faire
}

void Routeur::envoyerOSPF(Routeur& dest, PaquetOSPF& ospf) {
    dest.recevoirOSPF(ospf);
}

void Routeur::recevoirOSPF(PaquetOSPF& ospf) {
    m_FilePaquetsOSPF.emplace(ospf);
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

/*
void Routeur::traitementPaquetOSPF() {
    // Recuperation du paquet en debut de file.
    PaquetOSPF &paquet = dynamic_cast<PaquetOSPF&>(m_FilePaquetsOSPF.front());

    // Appel a la methode adequate en fonction du type de paquet.
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
    // L'identifiant du voisin ne correspond pas avec l'identifiant du routeur courant.
    if (hello.getIdVoisin() != m_IdRouteur) {
        return;
    }

    for (auto iter: m_TableRoutage) {
        // Le routeur est connu, on lui envoie un paquet DBD.
        if (iter.first->getIdRouteur() == hello.getIdRouteur()) {
            std::vector<LSA> annonces;

            // Initialisions de la liste des annonces LSA.
            for (auto routeur: m_TableRoutage) {
                LSA lsa(routeur.first->getIdRouteur(),
                        routeur.first->getIdRouteur(),
                        routeur.first->getSousReseau()
                );
                annonces.emplace_back(lsa);
            }

            // Envoie d'un paquet DBD au routeur nous envoyant le paquet Hello.
            auto destinataire = iter.first;
            PaquetDBD reponse(annonces);
            reponse.setEntete(DBD, m_IdRouteur);
            envoyerOSPF(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

            // Sortie immediate de la fonction.
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

            // Le routeur de l'annonce est inconnu.
            if (annonce.getIdRouteur() != routeur->getIdRouteur()) {
                bool trouve = false;

                // Verification qu'il ne se trouve pas plus loin dans la table de routage.
                for (auto verif: m_TableRoutage) {
                    if (verif.first->getIdRouteur() == routeur->getIdRouteur()) {
                        trouve = true;
                        break;
                    }
                }

                // Le routeur est inconnu, on ajoute l'identifiant du LSA
                // aux identifiant a demander.
                if (!trouve) {
                    idADemander.emplace_back(annonce.getIdLSA());
                }
            }
        }
    }

    // Le vecteur d'identifiant n'est pas vide, on doit envoyer un paquet LSR.
    if (!idADemander.empty()) {
        for (auto iter: m_TableRoutage) {
            if (iter.first->getIdRouteur() == dbd.getIdRouteur()) {
                auto destinataire = iter.first;
                // Ajout des identifiants demandes a la table.
                m_TableLSADemandes.emplace(std::make_pair(*destinataire, idADemander));

                // Envoie d'un paquet LSR au routeur nous envoyant le paquet DBD.
                PaquetLSR reponse(dbd.getIdRouteur(), idADemander);
                reponse.setEntete(LSR, m_IdRouteur);
                envoyerOSPF(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

                // Sortie immediate de la fonction.
                return;
            }
        }
    }
}

void Routeur::traitementPaquetLSR(PaquetLSR& lsr) {
    // L'identifiant du voisin ne correspond pas avec l'identifiant du routeur courant.
    if (lsr.getIdAnnonceur() != m_IdRouteur) {
        return;
    }

    auto vec = lsr.getIdLSADemandes();
    std::vector<LSA> annoncesDemandes;

    for (auto id: vec) {
        for (auto iter: m_TableRoutage) {
            auto routeur = iter.first;

            // L'identifiant du routeur correspond au LSA demande, on l'ajoute a la liste.
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

            // Ajout des identifiants des annonces a la table des LSA envoyes
            std::vector<std::bitset<32>> idAnnoncesDemandes;
            for (auto annonce: annoncesDemandes) {
                idAnnoncesDemandes.push_back(annonce.getIdLSA());
            }
            m_TableLSAEnvoyes.emplace(std::make_pair(*destinataire, idAnnoncesDemandes));

            // Envoie d'un paquet DBD au routeur envoyant le paquet Hello.
            PaquetLSU reponse(annoncesDemandes);
            reponse.setEntete(LSU, m_IdRouteur);
            envoyerOSPF(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

            // Sortie immediate de la fonction.
            return;
        }
    }
}

void Routeur::traitementPaquetLSU(PaquetLSU& lsu) {
    auto annonces = lsu.getLSADemandes();
    std::vector<std::bitset<32>> idLSARecus;

    for (auto annonce: annonces) {
        for (auto verif: m_TableLSADemandes) {
            if (verif.first->getIdRouteur() == lsu.getIdRouteur()) {
                for (auto id: *verif.second) {
                    if (id == annonce.getIdLSA()) {
                        idLSARecus.push_back(id);
                        m_TableLSADemandes.erase(verif.first);
                        // routageDynamique();
                        // m_TableRoutage.emplace();
                    }
                }
            }
        }
    }

    for (auto iter: m_TableLSADemandes) {
        if (iter.first->getIdRouteur() == lsu.getIdRouteur() && !iter.second->empty()) {
            // Envoie d'un paquet LSR au routeur envoyant le paquet LSU,
            // dans le cas ou il manque des LSAs.
            PaquetLSR reponse(iter.first->getIdRouteur(), *iter.second);
            reponse.setEntete(LSR, m_IdRouteur);
            envoyerOSPF(*iter.first, dynamic_cast<PaquetOSPF&>(reponse));

            // Sortie immediate de la fonction.
            return;
        }
    }

    for (auto iter: m_TableRoutage) {
        auto destinataire = iter.first;

        // Envoie d'un paquet LSAck au routeur envoyant le paquet LSU.
        if (destinataire->getIdRouteur() == lsu.getIdRouteur()) {
            PaquetLSAck reponse(idLSARecus);
            reponse.setEntete(LSAck, m_IdRouteur);
            envoyerOSPF(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

            // Sortie immediate de la fonction.
            return;
        }
    }
}

void Routeur::traitementPaquetLSAck(PaquetLSAck& ack) {
    auto idLSARecus = ack.getIdLSARecus();
    std::vector<LSA> LSAManquants;

    for (auto idAnnonce: idLSARecus) {
        for (auto iter: m_TableLSAEnvoyes) {
            if (iter.first->getIdRouteur() == ack.getIdRouteur()) {
                auto vec = *iter.second;

                for (auto idEnvoye = 0; idEnvoye < vec.size(); idEnvoye++) {
                    if (vec[idEnvoye] == idAnnonce) {
                        vec.erase(vec.cbegin() + idEnvoye - 1);
                    }
                }
            }
        }
    }

    for (auto iter: m_TableLSAEnvoyes) {
        if (iter.first->getIdRouteur() == ack.getIdRouteur() && !iter.second->empty()) {
            auto destinataire = iter.first;

            for (auto idManquant: *iter.second) {
                for (auto iter2: m_TableRoutage) {
                    auto routeur = iter2.first;

                    if (routeur->getIdRouteur() == (uint8_t)(idManquant.to_ulong())) {
                        LSA LSAManquant(routeur->getIdRouteur(),
                                        routeur->getIdRouteur(),
                                        routeur->getSousReseau()
                        );
                        LSAManquants.emplace_back(LSAManquant);
                    }
                }
            }

            // Envoie d'un paquet LSU au routeur envoyant le paquet LSAck,
            // dans le cas ou il des LSA n'ont pas ete recus.
            PaquetLSU reponse(LSAManquants);
            reponse.setEntete(LSU, m_IdRouteur);
            envoyerOSPF(*destinataire, dynamic_cast<PaquetOSPF&>(reponse));

            // Sortie immediate de la fonction.
            return;
        }
    }
}
*/
