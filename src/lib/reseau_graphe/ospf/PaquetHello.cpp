/**
 * @file    PaquetHello.cpp
 * @brief   Implementation de la classe PaquetHello.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#include "PaquetHello.hpp"

/**
 * @brief Cree un objet PaquetHello.
 *
 * @param idRouteurVoisin L'identifiant du routeur destinataire du paquet Hello.
 */
PaquetHello::PaquetHello(const uint8_t& idRouteurVoisin)
    : m_IdVoisin(idRouteurVoisin)
{}

/**
 * @brief Detruit un objet PaquetHello.
 *
 * Le corps du destructeur est vide car tout les attributs
 * de la classe sont declares statiquement.
 */
PaquetHello::~PaquetHello() {}

/**
 * @brief Modifie les valeurs de l'entete definis par
 * la classe mere abstraite PaquetOSPF.
 *
 * @param type Le type du paquet.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 */
void PaquetHello::setEntete(const TypePaquet& type, const uint16_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_Type.
 *
 * @return Le type du paquet.
 */
const TypePaquet& PaquetHello::getType() const {
    return m_Type;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdRouteur.
 *
 * @return L'identifiant du routeur emetteur du paquet.
 */
const uint16_t& PaquetHello::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdVoisin.
 *
 * @return L'identifiant du routeur recepteur du paquet.
 */
const uint16_t& PaquetHello::getIdDestinataire() const {
    return m_IdVoisin;
}
