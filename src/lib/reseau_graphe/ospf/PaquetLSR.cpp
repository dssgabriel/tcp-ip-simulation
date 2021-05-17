/**
 * 
 * @file        PaquetLSR.cpp
 * @brief       Déclaration de la classe PaquetLSR.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/
#include "PaquetLSR.hpp"

/**
 * @brief Constructeur de la classe PaquetLSR.
 * 
 * @param idAnnonceur L'identifiant de l'annonceur.
 * @param idLSADemandes Le vecteur des identifiants des LSA demandes.
 **/ 
PaquetLSR::PaquetLSR(
    const uint8_t& idAnnonceur,
    const std::vector<std::bitset<32>>& idLSADemandes
) : m_IdAnnonceur(idAnnonceur)
{
    for (auto idLSA: idLSADemandes) {
        m_IdLSADemandes.emplace_back(idLSA);
    }
}

/**
 * @brief Destructeur de la classe PaquetLSR.
 * 
 * Le destructeur est vide car tout est gere directement par le 'garbage collector'.
 **/ 
PaquetLSR::~PaquetLSR() {}

/**
 * @brief Setter de l'ensemble des attributs de la classe PaquetOSPF.
 * 
 * @param type Le type du paquet, ici LSR.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 * 
 * @return void.
 **/ 
void PaquetLSR::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Getter de l'attribut de classe m_Type.
 * 
 * @return Le type du paquet.
 **/ 
const TypePaquet& PaquetLSR::getType() const {
    return m_Type;
}

/**
 * @brief Getter de l'attribut m_IdRouteur.
 * 
 * @return L'identifiant du routeur emetteur.
 **/ 
const uint8_t& PaquetLSR::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Getter de l'attribut m_IdAnnonceur.
 * 
 * @return L'identifiant de l'annonceur.
 */ 
const uint8_t& PaquetLSR::getIdAnnonceur() const {
    return m_IdAnnonceur;
}

/**
 * @brief Getter de l'attribut m_IdLSADemandes.
 * 
 * @return Un vecteur contenant l'ensemble des identifiants des LSA demandees.
 **/ 
std::vector<std::bitset<32>>& PaquetLSR::getIdLSADemandes() {
    return m_IdLSADemandes;
}
