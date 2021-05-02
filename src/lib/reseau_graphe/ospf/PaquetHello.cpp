#include "PaquetHello.hpp"

PaquetHello::PaquetHello(const uint8_t& idRouteurVoisin) :
    m_IdVoisin(idRouteurVoisin)
{}

PaquetHello::~PaquetHello() {}

void PaquetHello::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

const TypePaquet& PaquetHello::getType() const {
    return m_Type;
}

const uint8_t& PaquetHello::getIdRouteur() const {
    return m_IdRouteur;
}

const uint8_t& PaquetHello::getIdVoisin() const {
    return m_IdVoisin;
}
