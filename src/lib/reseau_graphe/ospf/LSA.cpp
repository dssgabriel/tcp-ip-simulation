/**
 * @file    LSA.cpp
 * @brief   Implementation de la classe LSA.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#include "LSA.hpp"

/**
 * @brief Cree un objet LSA.
 *
 * @param idLSA L'identifiant du LSA.
 * @param idRouteur L'identifiant du routeur dont on partage les informations.
 * @param adrSousReseaux Les adresses de sous reseaux du routeur.
 */
LSA::LSA(const std::bitset<32>& idLSA,
         const uint16_t& idRouteur,
         const std::vector<IPv4>& adrSousReseaux)
    : m_IdLSA(idLSA), m_IdRouteur(idRouteur)
{
    for (IPv4 adresse: adrSousReseaux) {
        m_AdrSousReseaux.emplace_back(adresse);
    }
}

/**
 * @brief Detruit un objet LSA.
 *
 * Le corps du destructeur est vide car tous les attributs
 * de la classe sont declares statiquement.
 */
LSA::~LSA() {}

/**
 * @brief Retourne une reference sur l'attribut m_IdLSA.
 *
 * @return L'identifiant du LSA.
 */
const std::bitset<32>& LSA::getIdLSA() const {
    return m_IdLSA;
}

/**
 * @brief Retourne une reference sur l'attribut m_IdRouteur.
 *
 * @return L'identifiant du routeur dont on partage les informations.
 */
const uint16_t& LSA::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Retourne une reference sur l'attribut m_AdrSousReseaux.
 *
 * @return La liste des adresses de sous reseaux du routeur.
 */
const std::vector<IPv4>& LSA::getAdrSousReseaux() const {
    return m_AdrSousReseaux;
}
