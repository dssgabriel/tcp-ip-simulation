/**
 * @file    PaquetLSU.hpp
 * @brief   Implementation de la classe PaquetLSU.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#include "PaquetLSU.hpp"

/**
 * @brief Cree un objet PaquetLSU.
 *
 * @param LSADemandes La liste contenant tous les LSAs qui ont ete demandes.
 */
PaquetLSU::PaquetLSU(const std::vector<LSA>& LSADemandes) {
    for (LSA lsa: LSADemandes) {
        m_LSADemandes.emplace_back(lsa);
    }
}

/**
 * @brief Detruit un objet PaquetLSU.
 *
 * Le corps du destructeur est vide car tout les attributs
 * de la classe sont declares statiquement.
 */
PaquetLSU::~PaquetLSU() {}

/**
 * @brief Modifie les valeurs de l'entete definis par
 * la classe mere abstraite PaquetOSPF.
 *
 * @param type Le type du paquet.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 */
void PaquetLSU::setEntete(const TypePaquet& type, const uint16_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_Type.
 *
 * @return Le type du paquet.
 */
const TypePaquet& PaquetLSU::getType() const {
    return m_Type;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdRouteur.
 *
 * @return L'identifiant du routeur emetteur du paquet.
 */
const uint16_t& PaquetLSU::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_LSADemandes.
 *
 * @return La liste des LSAs demandes par le routeur.
 */
std::vector<LSA>& PaquetLSU::getLSADemandes() {
    return m_LSADemandes;
}
