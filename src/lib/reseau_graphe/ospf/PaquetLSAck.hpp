#pragma once

#include <bitset>
#include <vector>

#include "PaquetOSPF.hpp"

class PaquetLSAck: public PaquetOSPF {
    private:
        std::vector<std::bitset<32>> m_IdLSARecus;

    public:
        PaquetLSAck(const std::vector<std::bitset<32>>& m_IdLSARecus);

        ~PaquetLSAck();

        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        std::vector<std::bitset<32>>& getIdLSARecus();
};
