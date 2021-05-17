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

// Methode
void Commutateur::envoyer() {
    // Vide la file de donnees.
    std::stack<std::bitset<16>> donneeRecu = suppDonnee();

    Physique couchePhy;
    Internet coucheInt;
    std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
    
    // On enleve le checksum, le ttl et le protocoleId. 
    std::bitset<16> checksum = paquet.top();
    paquet.pop();
    std::bitset<16> ttl_Protocole = paquet.top();
    paquet.pop();

    // On recupere l'adresse de destination.
    std::bitset<16> ipDestDC = paquet.top();
    paquet.pop();
    std::bitset<16> ipDestBA = paquet.top();
    paquet.pop();

    // Trouver l'adresse MAC de la prochaine machine.
    IPv4 ip;
    coucheInt.convertir(ip, ipDestBA, ipDestDC);
    MAC prochainStop = trouverMacDest(ip);

    // Encapsulation adresse IP de destination.
    paquet.push(ipDestBA);
    paquet.push(ipDestDC);

    // Encapsulation du checksun et de ttl_Protole.
    paquet.push(ttl_Protocole);
    paquet.push(checksum);

    // Trouver la machine voisine.
    Machine* voisine = getVoisin(prochainStop);

    // Traitement de la donnee.
    traitement(donneeRecu, prochainStop);

    // La machine suivante recois le paquet
    voisine->setDonnee(donneeRecu);
    voisine->recevoir();
}

void Commutateur::recevoir() {
    // TODO : A faire
}

void Commutateur::traitement(std::stack<std::bitset<16>> &trame, MAC nouvelleDest) {
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
    for(int i = 0; i < 3; ++i){
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

MAC Commutateur::trouverMacDest(const IPv4& ip) {
    auto trouve = m_CacheMem.find(ip);
    if(trouve != m_CacheMem.end()) {
        return trouve->second;
    }
    else {
        std::cout << "ERREUR : Aucune adresse MAC ne correspond à l'adresse IP indiqué\n";
        return macZero;
    }
}