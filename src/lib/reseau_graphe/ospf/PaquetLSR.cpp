#include "PaquetLSR.hpp"

PaquetLSR::PaquetLSR(
    const uint8_t& idAnnonceur,
    const std::vector<std::bitset<32>>& idLSADemandes
) : m_IdAnnonceur(idAnnonceur)
{
    for (auto idLSA: idLSADemandes) {
        m_IdLSADemandes.emplace_back(idLSA);
    }
}

PaquetLSR::~PaquetLSR() {}

void PaquetLSR::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

const TypePaquet& PaquetLSR::getType() const {
    return m_Type;
}

const uint8_t& PaquetLSR::getIdRouteur() const {
    return m_IdRouteur;
}

const uint8_t& PaquetLSR::getIdAnnonceur() const {
    return m_IdAnnonceur;
}

std::vector<std::bitset<32>>& PaquetLSR::getIdLSADemandes() {
    return m_IdLSADemandes;
}
