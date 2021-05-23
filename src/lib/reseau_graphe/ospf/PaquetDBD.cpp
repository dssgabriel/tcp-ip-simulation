/**
 * @file    PaquetDBD.cpp
 * @brief   Implementation de la classe PaquetDBD.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#include "PaquetDBD.hpp"

/**
 * @brief Cree un objet PaquetDBD.
 *
 * @param LSAs La liste des LSAs a envoyer.
 */
PaquetDBD::PaquetDBD(const std::vector<LSA>& LSAs) {
    for (LSA lsa: LSAs) {
        m_LSAs.emplace_back(lsa);
    }
}

/**
 * @brief Detruit un objet PaquetDBD.
 *
 * Le corps du destructeur est vide car tout les attributs
 * de la classe sont declares statiquement.
 */
PaquetDBD::~PaquetDBD() {}

/**
 * @brief Modifie les valeurs de l'entete definis par
 * la classe mere abstraite PaquetOSPF.
 *
 * @param type Le type du paquet.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 */
void PaquetDBD::setEntete(const TypePaquet& type, const uint16_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_Type.
 *
 * @return Le type du paquet.
 */
const TypePaquet& PaquetDBD::getType() const {
    return m_Type;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdRouteur.
 *
 * @return L'identifiant du routeur emetteur du paquet.
 */
const uint16_t& PaquetDBD::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_LSAs.
 *
 * @return La liste des LSAs envoyes dans le paquet.
 */
std::vector<LSA>& PaquetDBD::getLSAs() {
    return m_LSAs;
}
