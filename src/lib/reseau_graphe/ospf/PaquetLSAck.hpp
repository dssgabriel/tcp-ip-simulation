/**
 * 
 * @file        PaquetLSAck.hpp
 * @brief       Déclaration de la classe PaquetLSAck.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/

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
        ~PaquetLSAck();

        // Setter & Getters
        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        std::vector<std::bitset<32>>& getIdLSARecus();
};
