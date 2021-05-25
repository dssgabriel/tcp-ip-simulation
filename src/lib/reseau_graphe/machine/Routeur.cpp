/**
 * @file    Routeur.cpp
 * @author  Mickael Le Denmat
 * @author  Gabriel Dos Santos
 * @brief   Vous trouverez ici toutes les fonctions implementees
 *          pour la classe Routeur
 * @date    2021-05-21
 */

#include <cstdlib>

#include "../ReseauGraphe.hpp"
#include "Commutateur.hpp"

uint16_t Routeur::m_NbRouteur = 0;

/**
 * @brief Constructeur de la classe Routeur.
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
 */
Routeur::~Routeur() {
    m_NbRouteur--;
}

/**
 * @brief Accesseur du nombre de routeur.
 *
 * @return uint16_t le nombre de routeur.
 */
uint16_t Routeur::getNbRouteur() {
    return m_NbRouteur;
}

/**
 * @brief Accesseur de l'identifiant du routeur.
 *
 * @return uint16_t l'identifiant du routeur.
 */
uint16_t Routeur::getIdRouteur() {
    return m_IdRouteur;
}

void Routeur::setTableRoutage(Routeur* r, Liaison* l) {
    std::vector<Liaison*> chemin(1, l);
    m_TableRoutage[r] = chemin;
}

/**
 * @brief Accesseur pour la table de routage.
 *
 * @return const std::map<Routeur*, std::vector<Liaison*>>& la table de routage.
 */
std::map<Routeur*, std::vector<Liaison*>>& Routeur::getTableRoutage() {
    return m_TableRoutage;
}

/**
 * @brief Envoie les trames de la file d'attente à la machine voisine.
 *
 * @param cwnd le nombre de trame a envoyer.
 * @param estAck indique la trame est un accuse de reception ou non.
 */
void Routeur::envoyer(const uint32_t cwnd, const bool estAck) {
    if (DEBUG) {
        std::cout << m_Nom << " : Debut envoie\n";
    }

    // Utilise pour le retour.
    if (estAck) {
        if (DEBUG) {
            std::cout << m_Nom << " : Retour\n";
        }

        // L'accuse de reception est la derniere valeur ajoute.
        std::stack<std::bitset<16>> donneeRecu = m_FileDonnees.back();
        m_FileDonnees.pop_back();

        // Creation des couches pour desencapsulation.
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Encapsulation.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        // Trouve le voisin.
        Machine* voisine = getVoisin(trouverMacDest(coucheInt.getIpSrc()));

        // Ajout de trame dans la file de donnee de la machine voisine.
        voisine->setDonnee(donneeRecu);
        voisine->recevoir(cwnd, true);

        if (DEBUG) {
            std::cout << m_Nom << " : Fin envoie\n";
        }
        return;
    } else {
        if (DEBUG) {
            std::cout << m_Nom << " : Aller\n";
        }

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

        // Encapsulation.
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
        if (DEBUG) {
            std::cout << m_Nom << " : Fin envoie\n";
        }
    }
}

/**
 * @brief Recois la trame.
 *
 * @param cwnd Le nombre de trame recu.
 * @param estAck La trame recu est un accuse de reception ou non.
 */
void Routeur::recevoir(const uint32_t cwnd, const bool estAck) {
    if (DEBUG) {
        std::cout << m_Nom << " : Debut recevoir\n";
    }
    envoyer(cwnd, estAck);
    if (DEBUG) {
        std::cout << m_Nom << " : Fin recevoir\n";
    }
}

/**
 * @brief Renvoie l'adresse MAC de la machine correspondante a l'adresse IP.
 *
 * @param ip de la machine qui nous interesse.
 * @return MAC correspondante.
 */
MAC Routeur::trouverMacDest(const IPv4 ip) {

    // On regarde la machine possedant l'adresse IP.
    Machine* m = ReseauGraphe::getMachine(ip);

    // Le routeur est il dans le meme sous reseau que l'ip ?
    for (IPv4 sousReseauRouteur : m_SousReseau) {
        for (IPv4 sousReseauDest : m->getSousReseaux()) {
            if (sousReseauRouteur == sousReseauDest) {
                for (Machine* v: m_Voisins) {
                    if (v->getMac() == m->getMac()) {
                        return v->getMac();
                    } else {
                        Commutateur* c = dynamic_cast<Commutateur*>(v);

                        if (c) {
                            for (IPv4 sousReseauCommutateur : c->getSousReseaux()) {
                                if (sousReseauCommutateur == sousReseauDest) {
                                    return c->getMac();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Trouver le chemin pour aller au routeur dans le meme sous reseau que l'ip dest.
    for (auto iter : m_TableRoutage) {
        std::vector<Liaison*> tabLiaison = iter.second;

        size_t derniereLiaison = tabLiaison.size() - 1;
        uint16_t idDerniereMachine1 = tabLiaison[derniereLiaison]->m_NumMachine1;
        uint16_t idDerniereMachine2 = tabLiaison[derniereLiaison]->m_NumMachine2;

        uint16_t idDernierRouteur1 = ReseauGraphe::getIdRouteurDepuisIdMachine(idDerniereMachine1);
        uint16_t idDernierRouteur2 = ReseauGraphe::getIdRouteurDepuisIdMachine(idDerniereMachine2);

        std::vector<Routeur*> derniersRouteurs;
        derniersRouteurs.emplace_back(ReseauGraphe::getPtrRouteur(idDernierRouteur1));
        derniersRouteurs.emplace_back(ReseauGraphe::getPtrRouteur(idDernierRouteur2));

        // Renvoie du routeur voisin.
        for (Routeur* dernierRouteur: derniersRouteurs) {
            for (IPv4 sousRes : dernierRouteur->getSousReseaux()) {
                if (sousRes == ReseauGraphe::getSousReseau(ip)) {
                    uint16_t idMachineDepart = tabLiaison[0]->m_NumMachine1 != getIdMachine() ?
                        tabLiaison[0]->m_NumMachine1 : tabLiaison[0]->m_NumMachine2;
                    uint16_t idRouteurDepart = ReseauGraphe::getIdRouteurDepuisIdMachine(idMachineDepart);
                    Routeur* routeurDepart = ReseauGraphe::getPtrRouteur(idRouteurDepart);

                    return routeurDepart->getMac();
                }
            }
        }
    }

    //
    std::cout << "ERREUR : Dans le fichier 'Routeur.cpp. "
        << "Dans la fonction 'trouverMacDest'. "
        << "Aucune adresse MAC trouvee\n";
    exit(EXIT_FAILURE);
}

void Routeur::envoyerOSPF(Routeur* destination, PaquetOSPF* ospf) {
    auto recherche = m_TableRoutage.find(destination);

    if (recherche != m_TableRoutage.end()) {
        Liaison chemin = *recherche->second[0];

        uint16_t idMachineProchain = chemin.m_NumMachine1 != getIdMachine() ?
            chemin.m_NumMachine1 : chemin.m_NumMachine2;

        uint16_t idRouteurProchain = ReseauGraphe::getIdRouteurDepuisIdMachine(idMachineProchain);

        Routeur* prochain = ReseauGraphe::getPtrRouteur(idRouteurProchain);

        if (prochain != nullptr) {
            prochain->recevoirOSPF(ospf);
        } else {
            std::cout << "ERREUR : fichier `Routeur.cpp`\n"
                << "\tmethode `envoyerOSPF` : "
                << "Pointeur invalide sur le routeur #" << idRouteurProchain
                << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void Routeur::recevoirOSPF(PaquetOSPF* ospf) {
    m_FilePaquetsOSPF.push_back(ospf);
    traitementPaquetOSPF();
}

void Routeur::traitementPaquetOSPF() {
    // Recuperation du paquet en debut de file.
    PaquetOSPF* paquet = m_FilePaquetsOSPF.front();
    m_FilePaquetsOSPF.pop_front();

    if (paquet != nullptr) {
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
                std::cout << "ERREUR : fichier `Routeur.cpp`\n"
                    << "\tmethode `traitementPaquetOSPF`: "
                    << "Type de PaquetOSPF inconnu"
                    << std::endl;
                exit(EXIT_FAILURE);
        }
    } else {
        std::cout << "ERREUR : fichier `Routeur.cpp`\n"
            << "\tmethode `traitementPaquetOSPF`: "
            << "Pointeur sur PaquetOSPF invalide"
            << std::endl;
    m_FilePaquetsOSPF.clear();
        exit(EXIT_FAILURE);
    }
}

// Methodes privees
void Routeur::traitementPaquetHello(PaquetHello* hello) {
    // L'identifiant du voisin ne correspond pas avec l'identifiant du routeur courant.
    if (hello->getIdDestinataire() != m_IdRouteur) {
        std::cout << "ERREUR : fichier `Routeur.cpp`\n"
            << "\tmethode `traitementPaquetHello` : "
            << "Identifiant du routeur (#" << m_IdRouteur
            << ") ne correspond pas avec le routeur destinataire du paquet (#"
            << hello->getIdDestinataire() << ")" << std::endl;

        delete hello;
        exit(EXIT_FAILURE);
    }

    Routeur* destinataire = ReseauGraphe::getPtrRouteur(hello->getIdRouteur());
    if (destinataire) {
        std::vector<LSA> listeLSAs;

        // Initialisions de la liste des annonces LSA.
        for (auto iter: m_TableRoutage) {
            Routeur* routeur = iter.first;
            LSA lsa(routeur->getIdRouteur(),
                    routeur->getIdRouteur(),
                    routeur->getSousReseaux()
            );
            listeLSAs.emplace_back(lsa);
        }

        // Envoie d'un paquet DBD au routeur emetteur du paquet Hello.
        PaquetOSPF* reponse = new PaquetDBD(listeLSAs);
        reponse->setEntete(DBD, m_IdRouteur);

        delete hello;
        envoyerOSPF(destinataire, reponse);
    } else {
        std::cout << "ERREUR : fichier `Routeur.cpp`\n"
            << "\tmethode `traitementPaquetHello` : "
            << "Le routeur destinataire (#" << hello->getIdRouteur() << ") n'existe pas"
            << std::endl;

        delete hello;
        exit(EXIT_FAILURE);
    }
}

void Routeur::traitementPaquetDBD(PaquetDBD* dbd) {
    std::vector<LSA> LSAs = dbd->getLSAs();
    std::vector<std::bitset<32>> idADemander;

    for (LSA lsa: LSAs) {
        bool trouve = false;

        if (lsa.getIdRouteur() == m_IdRouteur) {
            trouve = true;
            continue;
        }

        for (auto iter: m_TableRoutage) {
            Routeur* routeur = iter.first;

            if (lsa.getIdRouteur() == routeur->getIdRouteur()) {
                trouve = true;
            }
        }

        if (!trouve) {
            idADemander.emplace_back(lsa.getIdLSA());
        }
    }

    Routeur* destinataire = ReseauGraphe::getPtrRouteur(dbd->getIdRouteur());
    // Le vecteur d'identifiant n'est pas vide, on doit envoyer un paquet LSR.
    if (destinataire != nullptr) {
        if (!idADemander.empty()) {
            // Ajout des identifiants demandes a la table.
            m_TableLSADemandes.emplace(destinataire, idADemander);

            // Envoie d'un paquet LSR au routeur nous envoyant le paquet DBD.
            PaquetOSPF* reponse = new PaquetLSR(destinataire->getIdRouteur(), idADemander);
            reponse->setEntete(LSR, m_IdRouteur);

            delete dbd;
            envoyerOSPF(destinataire, reponse);
        } else {
            // Rien a demander
            delete dbd;
        }
    } else {
        std::cout << "ERREUR : fichier `Routeur.cpp`\n"
            << "\tmethode `traitementPaquetDBD` : "
            << "Le routeur destinataire (#" << dbd->getIdRouteur() << ") n'existe pas"
            << std::endl;

        delete dbd;
        exit(EXIT_FAILURE);
    }
}

void Routeur::traitementPaquetLSR(PaquetLSR* lsr) {
    // L'identifiant du voisin ne correspond pas avec l'identifiant du routeur courant.
    if (lsr->getIdEmetteur() != m_IdRouteur) {
        std::cout << "ERREUR : fichier `Routeur.cpp`\n"
            << "\tmethode `traitementPaquetLSR` : "
            << "Identifiant du routeur (#" << m_IdRouteur
            << ") ne correspond pas avec le routeur emetteur du paquet DBD (#"
            << lsr->getIdEmetteur() << ")" << std::endl;

        delete lsr;
        exit(EXIT_FAILURE);
    }

    std::vector<std::bitset<32>> idDemandes = lsr->getIdLSADemandes();
    std::vector<LSA> LSAsDemandes;

    for (std::bitset<32> id: idDemandes) {
        for (auto iter: m_TableRoutage) {
            Routeur* routeur = iter.first;

            // L'identifiant du routeur correspond au LSA demande, on l'ajoute a la liste.
            if (routeur->getIdRouteur() == (uint16_t)(id.to_ulong())) {
                LSA lsa(routeur->getIdRouteur(),
                        routeur->getIdRouteur(),
                        routeur->getSousReseaux()
                );
                LSAsDemandes.emplace_back(lsa);
            }
        }
    }

    Routeur* destinataire = ReseauGraphe::getPtrRouteur(lsr->getIdRouteur());
    if (destinataire) {
        // Ajout des identifiants des annonces a la table des LSA envoyes
        m_TableLSAEnvoyes.emplace(destinataire, lsr->getIdLSADemandes());

        // Envoie d'un paquet DBD au routeur envoyant le paquet Hello.
        PaquetOSPF* reponse = new PaquetLSU(LSAsDemandes);
        reponse->setEntete(LSU, m_IdRouteur);

        delete lsr;
        envoyerOSPF(destinataire, reponse);
    } else {
        std::cout << "ERREUR : fichier `Routeur.cpp`\n"
            << "\tmethode `traitementPaquetLSR` : "
            << "Le routeur destinataire (#" << lsr->getIdRouteur() << ") n'existe pas"
            << std::endl;

        delete lsr;
        exit(EXIT_FAILURE);
    }
}

void Routeur::traitementPaquetLSU(PaquetLSU* lsu) {
    std::vector<LSA> LSAs = lsu->getLSADemandes();
    std::vector<std::bitset<32>> idLSARecus;
    std::vector<LSA> LSAMisAJour;
    bool estMisAJour = false;

    for (LSA lsa: LSAs) {
        bool estConnu = false;

        for (auto iter: m_TableRoutage) {
            Routeur* routeur = iter.first;

            if (routeur->getIdRouteur() == lsa.getIdRouteur()) {
                estConnu = true;
            }
        }

        if (!estConnu) {
            estMisAJour = true;

            idLSARecus.emplace_back(lsa.getIdLSA());
            LSA misAJour(lsa.getIdLSA(),
                         lsa.getIdRouteur(),
                         lsa.getAdrSousReseaux()
            );
            LSAMisAJour.emplace_back(misAJour);

            Routeur* routeur = ReseauGraphe::getPtrRouteur(lsa.getIdRouteur());
            m_TableRoutage[routeur] = ReseauGraphe::routageDynamique(
                    m_IdRouteur,
                    lsa.getIdRouteur()
            );
        }
    }

    if (estMisAJour) {
        for (auto iter: m_TableRoutage) {
            m_TableRoutage[iter.first] = ReseauGraphe::routageDynamique(
                m_IdRouteur,
                iter.first->getIdRouteur()
            );
        }

        for (Machine* machine: m_Voisins) {
            Routeur* routeur = dynamic_cast<Routeur*>(machine);

            if (routeur) {
                PaquetOSPF* miseAJour = new PaquetLSU(LSAMisAJour);
                miseAJour->setEntete(LSU, m_IdRouteur);
                envoyerOSPF(routeur, miseAJour);
            }
        }
    }

    auto recherche = m_TableLSAEnvoyes.find(ReseauGraphe::getPtrRouteur(lsu->getIdRouteur()));
    if (recherche != m_TableLSAEnvoyes.end()) {
        std::vector<std::bitset<32>> idLSAEnvoyes = recherche->second;

        for (size_t i = 0; i < idLSAEnvoyes.size(); ++i) {
            for (size_t j = 0; j < idLSARecus.size(); ++j) {
                if (idLSAEnvoyes[i] == idLSARecus[j]) {
                    idLSAEnvoyes.erase(idLSAEnvoyes.begin() + i);
                }
            }
        }

        if (!idLSAEnvoyes.empty()) {
            Routeur* destinataire = recherche->first;

            PaquetOSPF* reponse = new PaquetLSAck(idLSARecus);
            reponse->setEntete(LSAck, m_IdRouteur);
            envoyerOSPF(destinataire, reponse);
        }
    }

    delete lsu;
}

void Routeur::traitementPaquetLSAck(PaquetLSAck* ack) {
    std::vector<std::bitset<32>> idLSARecus = ack->getIdLSARecus();
    std::vector<LSA> LSAManquants;

    for (std::bitset<32> idLSARecu: idLSARecus) {
        for (auto iter: m_TableLSAEnvoyes) {
            Routeur* routeur = iter.first;
            std::vector<std::bitset<32>> idLSAEnvoyes = iter.second;

            if (routeur->getIdRouteur() == ack->getIdRouteur()) {
                for (size_t idLSAEnvoye = 0; idLSAEnvoye < idLSAEnvoyes.size(); ++idLSAEnvoye) {
                    if (idLSAEnvoyes[idLSAEnvoye] == idLSARecu) {
                        idLSAEnvoyes.erase(idLSAEnvoyes.begin() + idLSAEnvoye);
                    }
                }
            }
        }
    }

    Routeur* destinataire = ReseauGraphe::getPtrRouteur(ack->getIdRouteur());
    auto recherche = m_TableLSAEnvoyes.find(destinataire);

    if (recherche != m_TableLSAEnvoyes.end()) {
        if (!recherche->second.empty()) {
            std::vector<std::bitset<32>> idLSAManquants = recherche->second;
            for (std::bitset<32> idLSAManquant: idLSAManquants) {
                for (auto iter: m_TableRoutage) {
                    Routeur* routeur = iter.first;

                    if (routeur->getIdRouteur() == (uint16_t)(idLSAManquant.to_ulong())) {
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

            delete ack;
            envoyerOSPF(destinataire, reponse);
        } else {
            // Aucun LSA manquants, rien a renvoyer
            delete ack;
        }
    }
}

std::ostream& operator<<(std::ostream& flux, Routeur& r) {
    Machine& m = dynamic_cast<Machine&>(r);
    flux << m;

    flux << "ID Routeur : " << r.getIdRouteur() << std::endl;
    flux << "Table de routage :\n";
    for (auto it : r.getTableRoutage()) {
        std::cout << "\tVers Routeur " << it.first->getIdRouteur()
            << " (Machine " << it.first->getIdMachine() << ")" << std::endl;
        for (Liaison* l : it.second) {
            flux << "\t\t" << *l << std::endl;
        }
    }

    return flux;
}
