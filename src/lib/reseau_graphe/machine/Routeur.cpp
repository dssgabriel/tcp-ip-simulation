/**
 * @file Routeur.cpp
 * @author Mickael LE DENMAT
 *          Gabriel DOS SANTOS
 * @brief Vous trouverez ici toutes les fonctions implementees
 *          pour la classe Routeur.
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../ReseauGraphe.hpp"

uint8_t Routeur::m_NbRouteur = 0;

/**
 * @brief Constructeur de la classe Routeur.
 * 
 */
Routeur::Routeur() : Machine() {
    m_NbRouteur++;
    m_IdRouteur = m_NbRouteur;

    m_Nom = "Routeur" + std::to_string(m_IdRouteur);

    m_TableRoutage.clear();
    m_TableLSADemandes.clear();
    m_TableLSAEnvoyes.clear();
}

/**
 * @brief Destructeur de la classe Routeur.
 * 
 */
Routeur::~Routeur() {}

/**
 * @brief Accesseur du nombre de routeur.
 * 
 * @return uint8_t le nombre de routeur.
 */
uint8_t Routeur::getNbRouteur() {
    return m_NbRouteur;
}

/**
 * @brief Accesseur de l'identifiant du routeur.
 * 
 * @return uint8_t l'identifiant du routeur.
 */
uint8_t Routeur::getIdRouteur() {
    return m_IdRouteur;
}

/**
 * @brief Envoie les trames de la file d'attente à la machine voisine.
 * 
 * @param cwnd le nombre de trame a envoyer. 
 * @param estAck indique la trame est un accuse de reception ou non.
 */
void Routeur::envoyer(const uint32_t cwnd, const bool estAck) {
    std::cout << m_Nom << " : Debut envoie\n";

    // Utilise pour le retour.
    if (estAck) {
        std::cout << m_Nom << " : Retour\n";

        // L'accuse de reception est la derniere valeur ajoute.
        std::stack<std::bitset<16>> donneeRecu = m_FileDonnees.back();

        // Creation des couches pour desencapsulation.
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Encapsulation
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        // Trouve le voisin.
        Machine* voisine = getVoisin(trouverMacDest(coucheInt.getIpSrc()));
        
        // Ajout de trame dans la file de donnee de la machine voisine.
        voisine->setDonnee(donneeRecu);
        voisine->recevoir(cwnd, true);
        
        std::cout << m_Nom << " : Fin envoie\n";
        return;
    }
    else {
        std::cout << m_Nom << " : Aller\n";

        // Creation des couches pour desencapsulation.
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // Vide la file de donnees.
        std::stack<std::bitset<16>> donneeRecu = suppDonnee();

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Encapsulation
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        // Trouve le voisin.
        Machine* voisine = getVoisin(trouverMacDest(coucheInt.getIpDest()));

        // Traitement de la donnee.
        traitement(donneeRecu, voisine->getMac());

        // Ajout de trame dans la file de donnee de la machine voisine.
        voisine->setDonnee(donneeRecu);

        // Envoie des cwnd trames.
        for (int i = 1; i < int(cwnd); ++i) {
            // Vide la file de donnees.
            std::stack<std::bitset<16>> donneeRecu = suppDonnee();

            // Desencapsulation.
            std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
            std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
            std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

            // Encapsulation
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            donneeRecu = couchePhy.encapsuler(paquet);
            
            // Traitement de la trame.
            traitement(donneeRecu, voisine->getMac());

            // Ajout de trame dans la file de donnee de la machine voisine.
            voisine->setDonnee(donneeRecu);
        }

        //
        voisine->recevoir(cwnd, false);
        std::cout << m_Nom << " : Fin envoie\n";
    }
}

/**
 * @brief Recois la trame.
 * 
 * @param cwnd Le nombre de trame recu.
 * @param estAck La trame recu est un accuse de reception ou non.
 */
void Routeur::recevoir(const uint32_t cwnd, const bool estAck) {
    std::cout << m_Nom << " : Debut recevoir\n";
    envoyer(cwnd, estAck);
    std::cout << m_Nom << " : Fin recevoir\n";
}

/**
 * @brief Renvoie l'adresse MAC de la machine correspondante a l'adresse IP.
 * 
 * @param ip de la machine qui nous interesse.
 * @return MAC correspondante.
 */
MAC Routeur::trouverMacDest(const IPv4 ip) {
    Machine* m = ReseauGraphe::getMachine(ip);
    
    // Convertion de la machine en ordinateur ou en commutateur.
    if (static_cast<Ordinateur*>(m)
    || static_cast<Commutateur*>(m))
    {   
        // ???
        for (IPv4 masqueSousReseau : m->getSousReseaux()) {
            if (masqueSousReseau == ReseauGraphe::getSousReseau(ip)) {
                return m->getMac();
            }
        }
    }

    // ???
    for (auto iter : m_TableRoutage) {
        std::vector<Liaison*> tabLiaison = iter.second;
        uint16_t routeurArrive = tabLiaison[tabLiaison.size() - 1]->m_NumMachine2;
        Routeur r = ReseauGraphe::getRouteur(uint8_t(routeurArrive));
        
        // ???
        for (IPv4 sousRes : r.getSousReseaux()) {
            if (sousRes == ReseauGraphe::getSousReseau(ip)) {
                return r.getMac();
            }
        }
    }

    //
    std::cout << "ERREUR : Dans le fichier 'Routeur.cpp. ";
    std::cout << "Dans la fonction 'trouverMacDest'. ";
    std::cout << "Aucune adresse MAC trouvee\n";
    exit(EXIT_FAILURE);
}

void Routeur::envoyerOSPF(Routeur* dest, PaquetOSPF* ospf) {
    dest->recevoirOSPF(ospf);
}

void Routeur::recevoirOSPF(PaquetOSPF* ospf) {
    m_FilePaquetsOSPF.emplace(ospf);
}

void Routeur::traitementPaquetOSPF() {
    // Recuperation du paquet en debut de file.
    PaquetOSPF* paquet = m_FilePaquetsOSPF.front();

    // Appel a la methode adequate en fonction du type de paquet.
    switch (paquet->getType()) {
        case 1:
            traitementPaquetHello(dynamic_cast<PaquetHello*>(paquet));
            break;
        case 2:
            traitementPaquetDBD(dynamic_cast<PaquetDBD*>(paquet));
            break;
        case 3:
            traitementPaquetLSR(dynamic_cast<PaquetLSR*>(paquet));
            break;
        case 4:
            traitementPaquetLSU(dynamic_cast<PaquetLSU*>(paquet));
            break;
        case 5:
            traitementPaquetLSAck(dynamic_cast<PaquetLSAck*>(paquet));
            break;
        default:
            std::cout << "ERREUR : Dans le fichier 'Routeur.cpp'. ";
            std::cout << "Dans la fonction 'traitementPaquetOSPF'. ";
            std::cout << "Type de PaquetOSPF inconnu\n";
            return;
    }
}

// Methodes privees
void Routeur::traitementPaquetHello(PaquetHello* hello) {
    // L'identifiant du voisin ne correspond pas avec l'identifiant du routeur courant.
    if (hello->getIdVoisin() != m_IdRouteur) {
        delete hello;
        return;
    }

    for (auto iter: m_TableRoutage) {
        // Le routeur est connu, on lui envoie un paquet DBD.
        if (iter.first->getIdRouteur() == hello->getIdRouteur()) {
            std::vector<LSA> annonces;

            // Initialisions de la liste des annonces LSA.
            for (auto routeur: m_TableRoutage) {
                LSA lsa(routeur.first->getIdRouteur(),
                        routeur.first->getIdRouteur(),
                        routeur.first->getSousReseaux()
                );
                annonces.emplace_back(lsa);
            }

            // Envoie d'un paquet DBD au routeur nous envoyant le paquet Hello.
            auto destinataire = iter.first;
            PaquetDBD* reponse = new PaquetDBD(annonces);
            reponse->setEntete(DBD, m_IdRouteur);
            envoyerOSPF(destinataire, reponse);

            // Sortie immediate de la fonction.
            delete hello;
            return;
        }
    }
}

void Routeur::traitementPaquetDBD(PaquetDBD* dbd) {
    auto annonces = dbd->getAnnoncesLSA();
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
            if (iter.first->getIdRouteur() == dbd->getIdRouteur()) {
                auto destinataire = iter.first;
                // Ajout des identifiants demandes a la table.
                m_TableLSADemandes.emplace(std::make_pair(destinataire, &idADemander));

                // Envoie d'un paquet LSR au routeur nous envoyant le paquet DBD.
                PaquetLSR* reponse = new PaquetLSR(dbd->getIdRouteur(), idADemander);
                reponse->setEntete(LSR, m_IdRouteur);
                envoyerOSPF(destinataire, reponse);

                // Sortie immediate de la fonction.
                delete dbd;
                return;
            }
        }
    }
}

void Routeur::traitementPaquetLSR(PaquetLSR* lsr) {
    // L'identifiant du voisin ne correspond pas avec l'identifiant du routeur courant.
    if (lsr->getIdAnnonceur() != m_IdRouteur) {
        delete lsr;
        return;
    }

    auto vec = lsr->getIdLSADemandes();
    std::vector<LSA> annoncesDemandes;

    for (auto id: vec) {
        for (auto iter: m_TableRoutage) {
            auto routeur = iter.first;

            // L'identifiant du routeur correspond au LSA demande, on l'ajoute a la liste.
            if (routeur->getIdRouteur() == (uint8_t)(id.to_ulong())) {
                LSA lsa(routeur->getIdRouteur(),
                        routeur->getIdRouteur(),
                        routeur->getSousReseaux()
                );
                annoncesDemandes.emplace_back(lsa);
            }
        }
    }

    for (auto iter: m_TableRoutage) {
        if (lsr->getIdRouteur() == iter.first->getIdRouteur()) {
            auto destinataire = iter.first;

            // Ajout des identifiants des annonces a la table des LSA envoyes
            std::vector<std::bitset<32>> idAnnoncesDemandes;
            for (auto annonce: annoncesDemandes) {
                idAnnoncesDemandes.push_back(annonce.getIdLSA());
            }
            m_TableLSAEnvoyes.emplace(std::make_pair(destinataire, &idAnnoncesDemandes));

            // Envoie d'un paquet DBD au routeur envoyant le paquet Hello.
            PaquetLSU* reponse = new PaquetLSU(annoncesDemandes);
            reponse->setEntete(LSU, m_IdRouteur);
            envoyerOSPF(destinataire, reponse);

            // Sortie immediate de la fonction.
            delete lsr;
            return;
        }
    }
}

// TODO : Renvoyer des LSUs lorsqu'on en recoit et que l'on fait des mises a jours.
void Routeur::traitementPaquetLSU(PaquetLSU* lsu) {
    auto annonces = lsu->getLSADemandes();
    std::vector<std::bitset<32>> idLSARecus;

    for (auto annonce: annonces) {
        for (auto verif: m_TableLSADemandes) {
            if (verif.first->getIdRouteur() == lsu->getIdRouteur()) {
                for (auto id: *verif.second) {
                    if (id == annonce.getIdLSA()) {
                        idLSARecus.push_back(id);
                        m_TableLSADemandes.erase(verif.first);

                        Routeur routeur = ReseauGraphe::getRouteur(verif.first->getIdRouteur());
                        std::vector<Liaison*> plusCourtChemin = ReseauGraphe::routageDynamique(
                            routeur.getIdRouteur(),
                            m_IdRouteur
                        );
                        m_TableRoutage.emplace(&routeur, plusCourtChemin);
                    }
                }
            }
        }
    }

    for (auto iter: m_TableLSADemandes) {
        if (iter.first->getIdRouteur() == lsu->getIdRouteur() && !iter.second->empty()) {
            // Envoie d'un paquet LSR au routeur envoyant le paquet LSU,
            // dans le cas ou il manque des LSAs.
            auto destinataire = iter.first;
            PaquetLSR* reponse = new PaquetLSR(iter.first->getIdRouteur(), *iter.second);
            reponse->setEntete(LSR, m_IdRouteur);
            envoyerOSPF(destinataire, reponse);

            // Sortie immediate de la fonction.
            delete lsu;
            return;
        }
    }

    for (auto iter: m_TableRoutage) {
        auto destinataire = iter.first;

        // Envoie d'un paquet LSAck au routeur envoyant le paquet LSU.
        if (destinataire->getIdRouteur() == lsu->getIdRouteur()) {
            PaquetLSAck* reponse = new PaquetLSAck(idLSARecus);
            reponse->setEntete(LSAck, m_IdRouteur);
            envoyerOSPF(destinataire, reponse);

            // Sortie immediate de la fonction.
            delete lsu;
            return;
        }
    }
}

void Routeur::traitementPaquetLSAck(PaquetLSAck* ack) {
    auto idLSARecus = ack->getIdLSARecus();
    std::vector<LSA> LSAManquants;

    for (auto idAnnonce: idLSARecus) {
        for (auto iter: m_TableLSAEnvoyes) {
            if (iter.first->getIdRouteur() == ack->getIdRouteur()) {
                auto vec = *iter.second;

                for (size_t idEnvoye = 0; idEnvoye < vec.size(); idEnvoye++) {
                    if (vec[idEnvoye] == idAnnonce) {
                        vec.erase(vec.cbegin() + idEnvoye - 1);
                    }
                }
            }
        }
    }

    for (auto iter: m_TableLSAEnvoyes) {
        if (iter.first->getIdRouteur() == ack->getIdRouteur() && !iter.second->empty()) {
            auto destinataire = iter.first;

            for (auto idManquant: *iter.second) {
                for (auto iter2: m_TableRoutage) {
                    auto routeur = iter2.first;

                    if (routeur->getIdRouteur() == (uint8_t)(idManquant.to_ulong())) {
                        LSA LSAManquant(routeur->getIdRouteur(),
                                        routeur->getIdRouteur(),
                                        routeur->getSousReseaux()
                        );
                        LSAManquants.emplace_back(LSAManquant);
                    }
                }
            }

            // Envoie d'un paquet LSU au routeur envoyant le paquet LSAck,
            // dans le cas ou il des LSA n'ont pas ete recus.
            PaquetLSU* reponse = new PaquetLSU(LSAManquants);
            reponse->setEntete(LSU, m_IdRouteur);
            envoyerOSPF(destinataire, reponse);

            // Sortie immediate de la fonction.
            delete ack;
            return;
        }
    }
}
