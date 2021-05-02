#pragma once

#include <cstdint>

#include "PaquetOSPF.hpp"

class PaquetHello: public PaquetOSPF {
    private:
        uint8_t m_IdVoisin;

    public:
        PaquetHello(const uint8_t& idRouteurVoisin);

        ~PaquetHello();

        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        const uint8_t& getIdVoisin() const;
};
