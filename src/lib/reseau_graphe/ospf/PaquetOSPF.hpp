/**
 * @file    PaquetOSPF.hpp
 * @brief   Declaration de la classe abstraite PaquetOSPF.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#pragma once

#include <cstdint>

enum TypePaquet: uint8_t {
    Hello = 1,
    DBD = 2,
    LSR = 3,
    LSU = 4,
    LSAck = 5
};

class PaquetOSPF {
    protected:
        // Attributs
        TypePaquet m_Type;
        uint16_t m_IdRouteur;

    public:
        // Destructeur virtuel
        virtual ~PaquetOSPF() {}

        // Getters et setter
        virtual void setEntete(const TypePaquet& type, const uint16_t& idRouteur) = 0;
        virtual const TypePaquet& getType() const = 0;
        virtual const uint16_t& getIdRouteur() const = 0;
};
