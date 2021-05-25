/**
 * @file Commutateur.cpp
 * @author Mickael Le Denmat
 * @brief Vous trouverez ici toutes les fonctions implementees
 *          pour la classe Commutateur
 * @date 2021-05-21
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Commutateur.hpp"

uint8_t Commutateur::m_NbCommutateur = 0;

/**
 * @brief Constructeur de la classe Commutateur.
 *
 */
Commutateur::Commutateur() : Machine() {
    m_NbCommutateur++;
    m_IdCommutateur = m_NbCommutateur;

    m_Nom = "Commutateur" + std::to_string(m_IdCommutateur);
}

/**
 * @brief Destructeur de la classe Commutateur.
 *
 */
Commutateur::~Commutateur() {
    m_NbCommutateur--;
}

/**
 * @brief Accesseur du nombre de commutateur.
 *
 * @return uint8_t le nombre de commutateur.
 */
uint8_t Commutateur::getNbrCommutateur() {
    return m_NbCommutateur;
}

/**
 * @brief Accesseur de l'identifiant du commutateur.
 *
 * @return uint8_t l'identifiant du commutateur.
 */
uint8_t Commutateur::getIdCommutateur() {
    return m_IdCommutateur;
}

/**
 * @brief Ajout d'une paire ip/mac dans la table memoire du commutateur.
 *
 * @param ip de la machine destination.
 * @param mac de la machine voisine pour aller a la destination.
 */
void Commutateur::setMemoire(const IPv4* ip, const MAC* mac) {
    m_CacheMem.insert(std::pair<const IPv4*, const MAC*>(ip, mac));
}

/**
 * @brief Accesseur de la table memoire du commutateur.
 *
 * @return const std::map<const IPv4*, const MAC*>& la table memoire.
 */
const std::map<const IPv4*, const MAC*>& Commutateur::getMemoire() const {
    return m_CacheMem;
}

/**
 * @brief Envoie une trame.
 *
 * @param cwnd le nombre de trame a envoyer.
 * @param estAck indique si la trame est un accuse de reception.
 */
void Commutateur::envoyer(const uint32_t cwnd, const bool estAck) {
    if (DEBUG) {
        std::cout << m_Nom << " : Debut envoie\n";
    }

    if (estAck) { // Partie envoie des accuses de reception
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

        // Encapsulation
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        // Trouver le voisin.
        Machine* voisine = getVoisin(trouverMacDest(coucheInt.getIpSrc()));

        // Ajout de trame dans la file de donnee de la machine voisine.
        voisine->setDonnee(donneeRecu);
        voisine->recevoir(cwnd, true);

        if (DEBUG) {
            std::cout << m_Nom << " : Fin envoie\n";
        }
        return;
    }
    else { // Partie envoie des paquets.
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

            // Encapsulation.
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            donneeRecu = couchePhy.encapsuler(paquet);

            // Traitement de la donnee.
            traitement(donneeRecu, voisine->getMac());

            // Ajout de trame dans la file de donnee de la machine voisine.
            voisine->setDonnee(donneeRecu);
        }

        // Reception de la/des trames.
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
void Commutateur::recevoir(const uint32_t cwnd, const bool estAck) {
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
MAC Commutateur::trouverMacDest(const IPv4 ip) {
    for (auto it : m_CacheMem) {
        if(*it.first == ip) {
            return *it.second;
        }
    }

    //
    std::cout << "ERREUR : Dans le fichier 'Commutateur.cpp'. "
        "Dans la fonction 'trouverMacDest'. "
        "Aucune adresse MAC ne correspond à l'adresse IP indiqué.\n";
    exit(EXIT_FAILURE);
}

/**
 * @brief Redefinition de l'operateur d'affichage.
 *
 * @param flux a modifier avec les informations du commutateur.
 * @param c a afficher.
 * @return std::ostream& l'affichage des informations du commutateur.
 */
std::ostream& operator<<(std::ostream& flux, Commutateur& c) {
    Machine& m = dynamic_cast<Machine&>(c);
    flux << m;

    flux << "Table memoire :\n";
    for (auto it : c.getMemoire()) {
        flux << "\t" << *it.first << " -> " << *it.second << std::endl;
    }

    return flux;
}
