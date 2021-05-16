/**
 * 
 * @file        PaquetLSAck.hpp
 * @brief       Implémentation de la classe PaquetLSAck.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/

#include "PaquetLSAck.hpp"

/**
 * @brief Constructeur de la classe PaquetLSAck.
 * 
 * @param idLSARecus L'identifiant du LSA qui a été reçu.
 **/ 
PaquetLSAck::PaquetLSAck(const std::vector<std::bitset<32>>& idLSARecus) {
    for (auto idRecu: idLSARecus) {
        m_IdLSARecus.emplace_back(idRecu);
    }
}

/**
 * @brief Destructeur de la classe PaquetLSAck. 
 * 
 * Le destructeur est vide car c'est le 'garbage collector' qui gere tout.
 **/ 
PaquetLSAck::~PaquetLSAck() {}

/**
 * @brief Setter de l'ensemble des attributs de la classe PaquetOPSF.
 * 
 * @param type Le type du paquet, ici LSAck;
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 * 
 * @return void.
 **/ 
void PaquetLSAck::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Getter de l'attribut de classe m_Type.
 * 
 * @return Le type du paquet reçu.
 **/ 
const TypePaquet& PaquetLSAck::getType() const {
    return m_Type;
}

/**
 * @brief Gettter de l'attribut de classe m_IdRouteur. 
 * 
 * @return L'identifiant du routeur emetteur du paquet.
 **/
const uint8_t& PaquetLSAck::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Getter de l'attribut de classe m_IdLSARecus. 
 * 
 * @return Le vecteur contenant l'ensemble des LSA reçus.
 **/ 
std::vector<std::bitset<32>>& PaquetLSAck::getIdLSARecus() {
    return m_IdLSARecus;
}
