/** 
 * 
 * @file        LSA.cpp
 * @brief       Implémentation de la classe LSA.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/
#include "LSA.hpp"

/**
 * @brief Constructeur de la classe LSA.
 * 
 * @param idLSA L'identifiant du LSA.
 * @param idRouteur L'identifiant du routeur emettant la LSA.
 * @param sousAdressesRouteur La sous-adresse du routeur.
 **/ 
LSA::LSA(
    const std::bitset<32>& idLSA,
    const uint8_t& idRouteur,
    const std::vector<IPv4>& sousAdressesRouteur
) : m_IdLSA(idLSA), m_IdRouteur(idRouteur)
{
    for (auto adresse: sousAdressesRouteur) {
        m_SousAdressesRouteur.emplace_back(adresse);
    }
}

/**
 * @brief Destructeur de la classe LSA.
 * 
 * Le destructeur est vide car tout est gere directement par le 'garbage collector'.
 **/ 
LSA::~LSA() {}

/**
 * @brief Getter de l'attribut m_IdLSA.
 * 
 * @return L'identifiant du LSA.
 **/ 
const std::bitset<32>& LSA::getIdLSA() const {
    return m_IdLSA;
}

/**
 * Getter de l'attribut m_IdRouteur.
 * 
 * @return L'identifiant du routeut emettant la LSA.
 **/ 
const uint8_t& LSA::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Getter de l'attribut m_SousAdressesRouteur.
 * 
 * @return La sous-adresse du routeur.
 **/ 
const std::vector<IPv4>& LSA::getSousAdressesRouteur() const {
    return m_SousAdressesRouteur;
}
