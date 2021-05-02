#pragma once

#include <vector>

#include "LSA.hpp"
#include "PaquetOSPF.hpp"

class PaquetDBD: public PaquetOSPF {
    private:
        std::vector<LSA> m_AnnoncesLSA;

    public:
        PaquetDBD(const std::vector<LSA>& annoncesLSA);

        ~PaquetDBD();

        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        std::vector<LSA>& getAnnoncesLSA();
};
