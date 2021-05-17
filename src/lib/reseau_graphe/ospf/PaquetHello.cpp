/**
 * 
 * @file        PaquetHello.cpp
 * @brief       Implementation de la classe PaquetHello.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/

#include "PaquetHello.hpp"

/**
 * @brief Constructeur de la classe PaquetHello.
 * 
 * @param idRouteurVoisin L'identifiant du routeur recepteur du paquet Hello. 
 **/ 
PaquetHello::PaquetHello(const uint8_t& idRouteurVoisin) :
    m_IdVoisin(idRouteurVoisin)
{}

/**
 * @brief Destructeur de la classe PaquetHello.
 * 
 * Le destructeur est vide car tout gere directement par le 'garbage collector'.
 **/ 
PaquetHello::~PaquetHello() {}

/**
 * @brief Setter de l'ensemble des attributs de la classe PaquetOSPF.
 * 
 * @param type Le type du paquet, ici Hello.
 * @param idRouteur Identifiant du routeur emetteur du paquet.
 * 
 * @return void.
 **/ 
void PaquetHello::setEntete(const TypePaquet& type, const uint8_t& idRouteur) {
    m_Type = type;
    m_IdRouteur = idRouteur;
}

/**
 * @brief Getter de l'attribut m_Type.
 * 
 * @return Le type du paquet.
 **/ 
const TypePaquet& PaquetHello::getType() const {
    return m_Type;
}

/**
 * @brief Getter de l'attribut m_IdRouteur.
 * 
 * @return L'identifiant du routeur emetteur du paquet.
 **/ 
const uint8_t& PaquetHello::getIdRouteur() const {
    return m_IdRouteur;
}

/**
 * @brief Getter de l'attribut de classe m_IdVoisin.
 * 
 * @return L'identifiant du routeur recepteur du paquet.
 **/ 
const uint8_t& PaquetHello::getIdVoisin() const {
    return m_IdVoisin;
}
