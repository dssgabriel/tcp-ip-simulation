#include "Commutateur.hpp"

uint8_t Commutateur::m_NbrCommutateur = 0;

// Constructeurs
Commutateur::Commutateur() : Machine() {
    m_NbrCommutateur++;
    m_IdCommutateur = m_NbrCommutateur;

    m_Nom = "Commutateur" + std::to_string(m_IdCommutateur);
}

// Destructeur
Commutateur::~Commutateur() {}

// Getters
uint8_t Commutateur::getNbrCommutateur() {
    return m_NbrCommutateur;
}

uint8_t Commutateur::getIdCommutateur() {
    return m_IdCommutateur; 
}

void Commutateur::setMemoire(const IPv4* ip, const MAC* mac) {
    m_CacheMem.insert(std::pair<const IPv4*, const MAC*>(ip, mac));
}

const std::map<const IPv4*, const MAC*>& Commutateur::getMemoire() const {
    return m_CacheMem;
}

// Methode
void Commutateur::envoyer(const uint32_t cwnd, const bool isAck) {
    std::cout << m_Nom << " : Debut envoie\n";

    //
    if (isAck) {
        std::cout << "Retour\n";

        //
        std::stack<std::bitset<16>> donneeRecu = m_FileDonnees.back();

        //
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        //
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        //
        Machine* voisine = getVoisin(trouverMacDest(coucheInt.getIpSrc()));
        voisine->setDonnee(donneeRecu);
        voisine->recevoir(cwnd, true);
        
        std::cout << m_Nom << " : Fin envoie\n";
        return;
    }
    else {
        std::cout << "Aller\n";
        //
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // Vide la file de donnees.
        std::stack<std::bitset<16>> donneeRecu = suppDonnee();

        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Trouver la machine voisine.
        Machine* voisine = getVoisin(trouverMacDest(coucheInt.getIpDest()));

        //
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        // Traitement de la donnee.
        traitement(donneeRecu, voisine->getMac());

        // La machine suivante recois le paquet
        voisine->setDonnee(donneeRecu);

        //
        for (int i = 1; i < int(cwnd); ++i) {
            // Vide la file de donnees.
            std::stack<std::bitset<16>> donneeRecu = suppDonnee();

            // On desencapsule.
            std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
            std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
            std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

            //
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            donneeRecu = couchePhy.encapsuler(paquet);
            
            // Traitement de la donnee.
            traitement(donneeRecu, voisine->getMac());

            // La machine suivante recois le paquet
            voisine->setDonnee(donneeRecu);
        }

        //
        voisine->recevoir(cwnd, false);
        std::cout << m_Nom << " : Fin envoie\n";
    }
}

void Commutateur::recevoir(const uint32_t cwnd, const bool isAck) {
    std::cout << m_Nom << " : Debut recevoir\n";
    envoyer(cwnd, isAck);
    std::cout << m_Nom << " : Fin recevoir\n";
}

MAC Commutateur::trouverMacDest(const IPv4 ip) {
    
    //
    for (auto it = m_CacheMem.begin(); it != m_CacheMem.end(); ++it) {
        if(*it->first == ip) {
            return *it->second;
        }
    }

    //
    std::cout << "ERREUR : Dans la fonction 'trouverMacDest' : ";
    std::cout << "Aucune adresse MAC ne correspond à l'adresse IP indiqué\n";
    return macZero;
}

// Overloading
std::ostream& operator<<(std::ostream& flux, Commutateur& c) {
    Machine *m = dynamic_cast<Commutateur*>(&c);
    flux << *m;

    std::map<const IPv4*, const MAC*> cpyCacheMem = c.getMemoire();
    flux << "Cache memoire (taille : " << cpyCacheMem.size() << ") : \n";
    for (auto itMap = cpyCacheMem.begin(); itMap != cpyCacheMem.end(); ++itMap) {
        // flux << *itMap->first << " -> " << *itMap->second << std::endl;
        flux << itMap->first << " -> " << itMap->second << std::endl;
    }

    return flux;
}