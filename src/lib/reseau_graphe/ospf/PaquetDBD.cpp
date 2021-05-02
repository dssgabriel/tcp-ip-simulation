#include "PaquetDBD.hpp"

PaquetDBD::PaquetDBD(const std::vector<LSA>& annoncesLSA) {
    for (auto lsa: annoncesLSA) {
        m_AnnoncesLSA.emplace_back(lsa);
    }
}

PaquetDBD::~PaquetDBD() {}

void PaquetDBD::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

const TypePaquet& PaquetDBD::getType() const {
    return m_Type;
}

const uint8_t& PaquetDBD::getIdRouteur() const {
    return m_IdRouteur;
}

std::vector<LSA>& PaquetDBD::getAnnoncesLSA() {
    return m_AnnoncesLSA;
}
