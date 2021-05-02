#include "PaquetLSAck.hpp"

PaquetLSAck::PaquetLSAck(const std::vector<std::bitset<32>>& idLSARecus) {
    for (auto idRecu: idLSARecus) {
        m_IdLSARecus.emplace_back(idRecu);
    }
}

PaquetLSAck::~PaquetLSAck() {}

void PaquetLSAck::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

const TypePaquet& PaquetLSAck::getType() const {
    return m_Type;
}

const uint8_t& PaquetLSAck::getIdRouteur() const {
    return m_IdRouteur;
}

std::vector<std::bitset<32>>& PaquetLSAck::getIdLSARecus() {
    return m_IdLSARecus;
}
