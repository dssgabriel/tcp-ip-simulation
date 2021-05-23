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
        uint16_t m_IdVoisin;

    public:
        // Constructeur
        PaquetHello(const uint8_t& idRouteurVoisin);

        // Destructeur
        ~PaquetHello();

        // Getters et setter
        virtual void setEntete(const TypePaquet& type, const uint16_t& idRouteur) override;
        virtual const TypePaquet& getType() const override;
        virtual const uint16_t& getIdRouteur() const override;

        const uint16_t& getIdDestinataire() const;
};
