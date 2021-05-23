/**
 * @file    PaquetDBD.hpp
 * @brief   Declaration de la classe PaquetDBD.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#pragma once

#include <vector>

#include "LSA.hpp"
#include "PaquetOSPF.hpp"

class PaquetDBD: public PaquetOSPF {
    private:
        // Attribut
        std::vector<LSA> m_LSAs;

    public:
        // Constructeur
        PaquetDBD(const std::vector<LSA>& LSAs);

        // Destructeur
        virtual ~PaquetDBD();

        // Getters et setter
        virtual void setEntete(const TypePaquet& type, const uint16_t& idRouteur) override;
        virtual const TypePaquet& getType() const override;
        virtual const uint16_t& getIdRouteur() const override;

        std::vector<LSA>& getLSAs();
};
