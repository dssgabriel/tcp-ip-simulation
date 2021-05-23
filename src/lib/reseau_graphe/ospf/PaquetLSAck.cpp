/**
 * @file    PaquetLSAck.hpp
 * @brief   Implementation de la classe PaquetLSAck.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#include "PaquetLSAck.hpp"

/**
 * @brief Cree un objet PaquetLSAck.
 *
 * @param idLSARecus La liste d'identifiants des LSAs qui ont ete recu.
 */
PaquetLSAck::PaquetLSAck(const std::vector<std::bitset<32>>& idLSARecus) {
    for (std::bitset<32> id: idLSARecus) {
        m_IdLSARecus.emplace_back(id);
    }
}

/**
 * @brief Detruit un objet PaquetLSAck.
 *
 * Le corps du destructeur est vide car tout les attributs
 * de la classe sont declares statiquement.
 */
PaquetLSAck::~PaquetLSAck() {}

/**
 * @brief Modifie les valeurs de l'entete definis par
 * la classe mere abstraite PaquetOSPF.
 *
 * @param type Le type du paquet.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 */
void PaquetLSAck::setEntete(const TypePaquet& type, const uint16_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_Type.
 *
 * @return Le type du paquet.
 */
const TypePaquet& PaquetLSAck::getType() const {
    return m_Type;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdRouteur.
 *
 * @return L'identifiant du routeur emetteur du paquet.
 */
const uint16_t& PaquetLSAck::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdLSARecus.
 *
 * @return La liste d'identifiants des LSA recus.
 */
std::vector<std::bitset<32>>& PaquetLSAck::getIdLSARecus() {
    return m_IdLSARecus;
}
