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

    // Trouver la machine voisine.
    // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
    Machine* voisine = m_Voisins.front();

    // Traitement de la donnee.
    traitement(*donneeRecu, voisine->getMac());

    // La machine suivante recois le paquet
    voisine->setDonnee(donneeRecu);
    voisine->recevoir();
}

void Ordinateur::recevoir() {
    // Si y a tout les ack
        // return
    // else
    envoyer();
}

std::deque<std::stack<std::bitset<16>>> convertirQueueDeque(std::queue<std::stack<std::bitset<16>>*> queue) {
    std::deque<std::stack<std::bitset<16>>> dequeu;
    for (int i = 0; i < queue.size(); i++)
    {
        dequeu.push_back(*queue.front());
        queue.pop();
    }

    return dequeu;
    
}

int tripleACK(Machine machine) {
    Physique phy;
    Internet inter;
    Transport trans;
    std::queue<std::stack<std::bitset<16>>*> donnees;
    donnees = machine.getDonnees();
    std::deque<std::stack<std::bitset<16>>> donneesDeque;
    donneesDeque = convertirQueueDeque(donnees);
    for (int i = 0; i < donneesDeque.size() - 1; ++i) {
        
        std::stack<std::bitset<16>> tmp = phy.desencapsuler(donneesDeque[i]);
        tmp = inter.desencapsuler(tmp);
        std::bitset<16> tmpAck1 = tmp.top();
        tmp.pop();
        std::bitset<16> tmpAck2 = tmp.top();
        std::bitset<32> ack = concat(tmpAck1, tmpAck2);
        
        for (int j = i + 1; j < donneesDeque.size(); ++j) {
            std::stack<std::bitset<16>> tmp2 = phy.desencapsuler(donneesDeque[j]);
            tmp2 = inter.desencapsuler(tmp2);
            std::bitset<16> tmpAck3 = tmp2.top();
            tmp2.pop();
            std::bitset<16> tmpAck4 = tmp2.top();
            std::bitset<32> ack2 = concat(tmpAck3, tmpAck4);
            if (ack == ack2) {
                std::stack<std::bitset<16>> tmp3 = phy.desencapsuler(donneesDeque[j + 1]);
                tmp3 = inter.desencapsuler(tmp3);
                std::bitset<16> tmpAck5 = tmp3.top();
                tmp3.pop();
                std::bitset<16> tmpAck6 = tmp3.top();
                std::bitset<32> ack3 = concat(tmpAck5, tmpAck6);
                if (ack == ack3) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Ordinateur::traitement(std::stack<std::bitset<16>> &trame, MAC nouvelleDest) {
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
    MAC ancienneDest = couchePhy.convetir(macDestBA, macDestBD, macDestFE);

    // Desencapsule la MAC Source d'origine qui ne nous interesse plus.
    for(int i = 0; i < 3; ++i){
        trame.pop();
    }

    // Changement adresse MAC.
    couchePhy.setMacSrc(ancienneDest);
    couchePhy.setMacDest(nouvelleDest);
    couchePhy.encapsuler(trame);
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