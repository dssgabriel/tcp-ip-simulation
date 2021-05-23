/**
 * @file    PaquetLSR.cpp
 * @brief   Implementation de la classe PaquetLSR.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#include "PaquetLSR.hpp"

/**
 * @brief Cree un objet PaquetLSR.
 *
 * @param idEmetteur L'identifiant du routeur ayant emis les LSA demandes.
 * @param idLSADemandes La liste d'identifiants des LSA demandes.
 */
PaquetLSR::PaquetLSR(const uint16_t& idEmetteur,
                     const std::vector<std::bitset<32>>& idLSADemandes)
    : m_IdEmetteur(idEmetteur)
{
    for (std::bitset<32> idLSA: idLSADemandes) {
        m_IdLSADemandes.emplace_back(idLSA);
    }
}

/**
 * @brief Detruit un objet PaquetLSR.
 *
 * Le corps du destructeur est vide car tout les attributs
 * de la classe sont declares statiquement.
 */
PaquetLSR::~PaquetLSR() {}

/**
 * @brief Modifie les valeurs de l'entete definis par
 * la classe mere abstraite PaquetOSPF.
 *
 * @param type Le type du paquet.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 */
void PaquetLSR::setEntete(const TypePaquet& type, const uint16_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_Type.
 *
 * @return Le type du paquet.
 */
const TypePaquet& PaquetLSR::getType() const {
    return m_Type;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdRouteur.
 *
 * @return L'identifiant du routeur emetteur du paquet.
 */
const uint16_t& PaquetLSR::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdEmetteur.
 *
 * @return L'identifiant du routeur emetteur.
 */
const uint16_t& PaquetLSR::getIdEmetteur() const {
    return m_IdEmetteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdLSADemandes.
 *
 * @return La liste d'identifiants des LSAs demandes.
 */
std::vector<std::bitset<32>>& PaquetLSR::getIdLSADemandes() {
    return m_IdLSADemandes;
}
