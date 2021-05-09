#include "Ordinateur.hpp"

uint8_t Ordinateur::m_NbrOrdinateur = 0;

// Constructeurs
Ordinateur::Ordinateur() : Machine() {
    m_NbrOrdinateur++;
    m_IdOrdinateur = m_NbrOrdinateur;

    m_Nom = "Ordinateur" + std::to_string(m_IdOrdinateur);

    m_ControleCongestion.clear();
    m_TempsTraitementPaquet.clear();
}

// // Ordinateur(const std::string& nom) {}

// Destructeur
Ordinateur::~Ordinateur() {

}

// Getters
const uint8_t& Ordinateur::getNbrOrdinateur() const {
    return m_NbrOrdinateur;
}

const uint8_t& Ordinateur::getIdOrdinateur() const {
    return m_IdOrdinateur;
}

const std::vector<ElementControleCongestion>& Ordinateur::getControleCongestion() const {
    return m_ControleCongestion;
}
    
const ElementControleCongestion& Ordinateur::getControleCongestion(const int& position) const {
    if(position < 0 || position > (int)m_ControleCongestion.size()) {
        std::cout << "ERREUR : position en dehors du tableau.\n";
        exit(EXIT_FAILURE);
    }

    return m_ControleCongestion[position];
}

const std::map<uint16_t, double> Ordinateur::getTempsTraitementPaquet() const {
    return m_TempsTraitementPaquet;
}

double Ordinateur::getTempsTraitementPaquet(const uint16_t& cle) const {
    auto trouve = m_TempsTraitementPaquet.find(cle);
    if(trouve != m_TempsTraitementPaquet.end()) {
        return trouve->second;
    }
    else {
        std::cout << "ERREUR : Aucun paquet ne correspond au numero demandé.\n";
        return -1;
    }
}

// Methodes
void Ordinateur::remplirFileDonnees(const ParamInterface& config, const MAC& destination) {
    
    // Initialisation
    Transport coucheTrans;
    Internet coucheInt;
    Physique couchePhy;

    // Preparation des donnees
    for(size_t i = 0; i < config.m_NbPaquet; ++i) {

        // Encapsulation couche Transport
        coucheTrans.setPortSrc(coucheTrans.portAlea());
        coucheTrans.setPortDest(config.m_TypeFichier);
        coucheTrans.setCwnd(std::bitset<16>(0));
        coucheTrans.setSyn(std::bitset<16>(1));
        coucheTrans.setAck1(std::bitset<16>(0));
        coucheTrans.setSeq(std::bitset<32>(i));
        coucheTrans.setAck2(std::bitset<32>(0));
        coucheTrans.setChecksum(std::bitset<16>(0));
        std::stack<std::bitset<16>> segment = coucheTrans.encapsuler();

        // Encapsulation couche Internet
        coucheInt.setIpSrc(config.m_Source);
        coucheInt.setIpDest(config.m_Destination);
        coucheInt.setTTL(std::bitset<8> (100));
        coucheInt.setProtocoleId();
        std::stack<std::bitset<16>> paquet = coucheInt.encapsuler(segment);

        // Encapsulation couche Physique
        couchePhy.setMacSrc(m_Mac);
        couchePhy.setMacDest(destination);
        std::stack<std::bitset<16>> trame = couchePhy.encapsuler(paquet);
        
        //
        m_FileDonnees.push(&trame);
    }

    // Appel tcp ip ?
}

void Ordinateur::synchroniser() {
    // TODO : A faire
}

void Ordinateur::finDeSession() {
    // TODO : A faire
}

void Ordinateur::envoyer() {
    // Vide la file de donnees.
    std::stack<std::bitset<16>>* donneeRecu = m_FileDonnees.front();
    m_FileDonnees.pop();

    // Traitement de la donnee.
    Machine* voisine = m_Voisins.front();
    voisine->suppDonnee();
    traitement(*donneeRecu, voisine->getMac());

    // Trouver la machine voisine.
    // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
    voisine->setDonnee(donneeRecu);
    voisine->recevoir();
}

void Ordinateur::recevoir() {
    envoyer();
}

template <size_t N1>
void inverser(std::stack<std::bitset<N1>> &pile) {
    std::stack<std::bitset<N1>> pileInv;

    for(size_t i = 0; i < pile.size(); ++i) {
        pileInv.push(pile.top());
        pile.pop();
    }
}

void Ordinateur::traitement(std::stack<std::bitset<16>> &donnee, MAC nouvelleDest) {
    // Recuperation du paquet.
    Physique couchePhy;
    std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnee);
    
    // Recuperation adresse MAC destination.
    std::bitset<16> macDestAB, macDestCD, macDestEF;
    macDestAB = paquet.top();
    paquet.pop();
    macDestCD = paquet.top();
    paquet.pop();
    macDestEF = paquet.top();
    paquet.pop();
    MAC ancienneDest = couchePhy.convetirBitsEnMac(macDestAB, macDestCD, macDestEF);

    // Recuperation adresse MAC source.
    std::bitset<16> macSrcAB, macSrcCD, macSrcEF;
    macSrcAB = paquet.top();
    paquet.pop();
    macSrcCD = paquet.top();
    paquet.pop();
    macSrcEF = paquet.top();
    paquet.pop();
    MAC ancienneSrc = couchePhy.convetirBitsEnMac(macSrcAB, macSrcCD, macSrcEF);

    // Changement adresse MAC.
    std::bitset<48> nouvelleDestBit = couchePhy.convertirMacEnBits(nouvelleDest);
    std::bitset<48> nouvelleSrcBit = couchePhy.convertirMacEnBits(ancienneDest);
    std::stack<std::bitset<16>> pileNouvelleDestBit = couchePhy.decoupageMac(nouvelleDestBit);
    std::stack<std::bitset<16>> pileNouvelleSrcBit = couchePhy.decoupageMac(nouvelleSrcBit);
    inverser(pileNouvelleDestBit);
    for(size_t i = 0; i < pileNouvelleDestBit.size(); ++i) {
        pileNouvelleSrcBit.push(pileNouvelleDestBit.top());
        pileNouvelleDestBit.pop();
    }
}

/*
void congestionAvoidance(std::bitset<16>& cwnd) {
    int compteur = 0;
    int nombreAck = 0; // Faut compter les ack, donc desencapsuler.
    uint64_t cwndConvert = cwnd.to_ulong();
    
    for(int i = 0; i < nombreAck; ++i) {
        if(ack est dupliqué) {
            compteur++;
            if(compteur >= 3) {
                compteur = 0;
                // ssthresh = cwndConvert/2;
                fastRetransmit(seq, cwnd);
            }
        }
        else {
            cwndConvert += 1;
            cwnd = std::bitset<16> (cwndConvert);
        }
        if(timeout) {
            uint16_t ssthresh = cwndConvert / 2;
            cwndConvert = 1;
            cwnd = std::bitset<16> (cwndConvert);
            slowStart(cwnd, ssthresh);
        }
    }
}

void slowStart(std::bitset<16>& cwnd, uint16_t& ssthresh1) {
    int nombreAck = 0; // Faut compter les ack, donc desencapsuler.
    uint64_t cwndConvert = cwnd.to_ulong();
    if(cwndConvert < ssthresh1) {
        for(int i = 0; i < nombreAck; ++i) {
            if(cwndConvert >= ssthresh1) {
                congestionAvoidance(cwnd);
            }
            else {
                cwndConvert *= 2;
                cwnd = std::bitset<16> (cwndConvert);
            }
        }
    }
    else {
        congestionAvoidance(cwnd);
    }
}

void fastRetransmit(const std::bitset<32>& seq, std::bitset<16>& cwnd) {
    // sender.envoie(seq)
    fastRecovery(cwnd);
}

void fastRecovery(std::bitset<16>& cwnd) {
    uint64_t cwndConvert = cwnd.to_ulong();
    uint16_t ssthresh2 = cwndConvert / 2;
    cwndConvert = ssthresh2 + 3;
    cwnd = std::bitset<16>(cwndConvert);

    int nombreAck = 0; // Faut compter les ack, donc desencapsuler.
    for(int i = 0; i < nombreAck; ++i) {
        if(ack dupliqué) {
            cwndConvert += 1;
            cwnd = std::bitset<16>(cwndConvert);
        }
        if(ack non duplique) {
            cwndConvert = ssthresh2;
            cwnd = std::bitset<16>(cwndConvert);
            congestionAvoidance(cwnd);
        }
    }
}
*/