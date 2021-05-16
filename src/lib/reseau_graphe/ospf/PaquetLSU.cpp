/**
 * 
 * @file        PaquetLSU.hpp
 * @brief       Implémentation de la classe PaquetLSU.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/
#include "PaquetLSU.hpp"

/**
 * @brief Constructeur de la classe PaquetLSU.
 * 
 * @param LSADemandes Le vecteur contenant toutes les LSA qui ont été demandés.
 **/ 
PaquetLSU::PaquetLSU(const std::vector<LSA>& LSADemandes) {
    for (auto lsa: LSADemandes) {
        m_LSADemandes.emplace_back(lsa);
    }
}

/**
 * @brief Destructeur de la classe PaquetLSU.
 * 
 * Le destructeur est vide car tout est fait pas le 'garbage collector'.
 **/ 
PaquetLSU::~PaquetLSU() {}

/**
 * @brief Setter de l'ensemble des attributs de la classe PaquetOSPF.
 * 
 * @param type Le type du paquet, ici LSU.
 * @param idRouteur L'identifiant du routeur emetteur du paquet.
 * 
 * @return void.
 **/ 
void PaquetLSU::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Getter de l'attribut de classe m_Type.
 * 
 * @return Le type du paquet.
 **/ 
const TypePaquet& PaquetLSU::getType() const {
    return m_Type;
}

/**
 * @brief Getter de l'attribut m_IdRouteur.
 * 
 * @return L'identifinat du routeur emetteur du paquet.
 */ 
const uint8_t& PaquetLSU::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Getter de l'attribut m_LSADemandes.
 * 
 * @return Le vecteur contenant toutes les paquets de types LSA.
 **/ 
std::vector<LSA>& PaquetLSU::getLSADemandes() {
    return m_LSADemandes;
}
