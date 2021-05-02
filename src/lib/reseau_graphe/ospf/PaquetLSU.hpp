#pragma once

#include <vector>

#include "LSA.hpp"
#include "PaquetOSPF.hpp"

class PaquetLSU: public PaquetOSPF {
    private:
        std::vector<LSA> m_LSADemandes;

    public:
        PaquetLSU(const std::vector<LSA>& LSADemandes);

        ~PaquetLSU();

        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        std::vector<LSA>& getLSADemandes();
};
