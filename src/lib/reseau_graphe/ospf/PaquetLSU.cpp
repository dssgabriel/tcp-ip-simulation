#include "PaquetLSU.hpp"

PaquetLSU::PaquetLSU(const std::vector<LSA>& LSADemandes) {
    for (auto lsa: LSADemandes) {
        m_LSADemandes.emplace_back(lsa);
    }
}

PaquetLSU::~PaquetLSU() {}

void PaquetLSU::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

const TypePaquet& PaquetLSU::getType() const {
    return m_Type;
}

const uint8_t& PaquetLSU::getIdRouteur() const {
    return m_IdRouteur;
}

std::vector<LSA>& PaquetLSU::getLSADemandes() {
    return m_LSADemandes;
}
