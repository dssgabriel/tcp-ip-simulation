/**
 * 
 * @file        PaquetDBD.hpp
 * @brief       Déclaration de la classe PaquetDBD.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/

#pragma once

#include <vector>

#include "LSA.hpp"
#include "PaquetOSPF.hpp"

class PaquetDBD: public PaquetOSPF {
    private:
        // Attribut
        std::vector<LSA> m_AnnoncesLSA;

    public:
        // Constructeur
        PaquetDBD(const std::vector<LSA>& annoncesLSA);

        // Destructeur
        ~PaquetDBD();

        // Setter & Getters
        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        std::vector<LSA>& getAnnoncesLSA();
};
