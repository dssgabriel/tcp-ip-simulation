/**
 * 
 * @file        PaquetDBD.cpp
 * @brief       Implementation de la classe PaquetDBD.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/

#include "PaquetDBD.hpp"

/**
 * @brief Constructeur de la classe PaquetDBD.
 * 
 * Le constructeur se charge de remplir le vecteur m_AnnoncesLSA avec tout les lsa.
 * 
 * @param annoncesLSA
**/
PaquetDBD::PaquetDBD(const std::vector<LSA>& annoncesLSA) {
    for (auto lsa: annoncesLSA) {
        m_AnnoncesLSA.emplace_back(lsa);
    }
}

/**
 * @brief Destructeur de la classe PaquetDBD.
 * 
 * Le destructeur est vide car tout est directement gere par le 'garbage collector'.
 **/ 
PaquetDBD::~PaquetDBD() {}


/**
 * @brief Setter de l'attribut des attributs de la classe PaquetOSPF.
 * 
 * @param type Defini le type de paquet ici DBD.
 * @param idRouteur Identifiant du routeur emetteur du paquet.
 * 
 * @return void.
 **/
void PaquetDBD::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Getter de l'agurment m_Type.
 * 
 * @return Le type du paquet. 
 **/ 
const TypePaquet& PaquetDBD::getType() const {
    return m_Type;
}

/**
 * @brief Getter de l'argument de clase m_IdRouteur.
 * 
 * @return L'identifiant du routeur emetteur du paquet.
 **/ 
const uint8_t& PaquetDBD::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Getter de l'argument de classe m_AnnoncesLSA.
 * 
 * @return Le vecteur contenant tout les LSA.
 **/ 
std::vector<LSA>& PaquetDBD::getAnnoncesLSA() {
    return m_AnnoncesLSA;
}
