#include "LSA.hpp"

LSA::LSA(
    const std::bitset<32>& idLSA,
    const uint8_t& idRouteur,
    const std::vector<IPv4>& sousAdressesRouteur
) : m_IdLSA(idLSA), m_IdRouteur(idRouteur)
{
    for (auto adresse: sousAdressesRouteur) {
        m_SousAdressesRouteur.emplace_back(adresse);
    }
}

LSA::~LSA() {}

const std::bitset<32>& LSA::getIdLSA() const {
    return m_IdLSA;
}

const uint8_t& LSA::getIdRouteur() const {
    return m_IdRouteur;
}

const std::vector<IPv4>& LSA::getSousAdressesRouteur() const {
    return m_SousAdressesRouteur;
}
