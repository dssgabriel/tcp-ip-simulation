/**
 * @file    PaquetHello.hpp
 * @brief   Declaration de la classe PaquetHello.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

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

        // Getters et setter
        virtual void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        virtual const TypePaquet& getType() const override;
        virtual const uint8_t& getIdRouteur() const override;

        const uint8_t& getIdDestinataire() const;
};
