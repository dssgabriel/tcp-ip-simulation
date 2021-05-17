/**
 * 
 * @file        PaquetHello.hpp
 * @brief       Déclaration de la classe PaquetHello.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/

#pragma once

#include <cstdint>

#include "PaquetOSPF.hpp"

class PaquetHello: public PaquetOSPF {
    private:
        // Attribut
        uint8_t m_IdVoisin;

    public:
        // Constructeur
        PaquetHello(const uint8_t& idRouteurVoisin);

        // Destructeur
        ~PaquetHello();

        // Setter & Getters
        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        const uint8_t& getIdVoisin() const;
};
