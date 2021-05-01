#pragma once

#include <cstdint>
#include <bitset>

class LSA {
    private:
        std::bitset<32> m_IdLSA;
        uint8_t m_IdRouteur;
        std::vector<IPv4> m_SousAdressesRouteur;

    public:
        LSA(const std::bitset<32>& idLSA,
            const uint8_t& idRouteur,
            const std::vector<IPv4>& sousAdressesRouteur
        );

        ~LSA();

        const std::bitset<32>& getIdLSA() const;
        const uint8_t& getIdRouteur() const;
        const std::vector<IPv4>& getSousAdressesRouteur() const;
};
