#include "Ordinateur.hpp"

uint8_t Ordinateur::m_NbrOrdinateur = 0;

// Constructeurs
Ordinateur::Ordinateur() {
    m_NbrOrdinateur++;
    m_IdOrdinateur = m_NbrOrdinateur;

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
    // TODO : A faire
}

void Ordinateur::synchroniser() {
    // TODO : A faire
}

void Ordinateur::finDeSession() {
    // TODO : A faire
}

void Ordinateur::envoyer() {
    // TODO : A faire
}

void Ordinateur::recevoir() {
    // TODO : A faire
}

void Ordinateur::traitement() {
    // TODO : A faire
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
