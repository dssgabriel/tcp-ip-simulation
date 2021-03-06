/**
 * @file    PaquetLSAck.hpp
 * @brief   Declaration de la classe PaquetLSAck.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#pragma once

#include <bitset>
#include <vector>

#include "PaquetOSPF.hpp"

class PaquetLSAck: public PaquetOSPF {
    private:
        // Attribut
        std::vector<std::bitset<32>> m_IdLSARecus;

    public:
        // Constructeur
        PaquetLSAck(const std::vector<std::bitset<32>>& m_IdLSARecus);

        // Destructeur
        virtual ~PaquetLSAck();

        // Getters et setter
        virtual void setEntete(const TypePaquet& type, const uint16_t& idRouteur) override;
        virtual const TypePaquet& getType() const override;
        virtual const uint16_t& getIdRouteur() const override;

        std::vector<std::bitset<32>>& getIdLSARecus();
};
