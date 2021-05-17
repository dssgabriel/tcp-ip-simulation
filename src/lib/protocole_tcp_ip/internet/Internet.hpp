/**

 * @file        Internet.hpp
 * @brief       Déclaration de la classe Internet.
 * 
 * @author      Quentin GRUCHET 
 * @author      Fadi MECHRI
 * @date        2021

 **/

#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <stack>

#include "../../../include/IPv4.hpp"
#include "../../../include/Commun.hpp"

class Internet {
    private :
       // Attributs
        IPv4 m_IpSrc;
        IPv4 m_IpDest;
        std::bitset<8> m_TTL;
        std::bitset<8> m_ProtocoleId;
        std::bitset<16> m_Checksum;

    public :
    
        // Constructeur
        Internet();

        // Destructeur
        ~Internet();

        // Setters & getters
        void setIpSrc(IPv4 src);
        const IPv4& getIpSrc() const;

        void setIpDest(IPv4 dest);
        const IPv4& getIpDest() const;

        void setTTL(const std::bitset<8>& ttl);
        const std::bitset<8>& getTTL() const;

        void setProtocoleId();
        const std::bitset<8>& getProtocoleId() const;

        const std::bitset<16>& getChecksum() const;
        
        // Methodes
        std::bitset<32> convertir(const IPv4& adresse);
        void convertir(IPv4& ip,
            const std::bitset<16>& ipPartBA, 
            const std::bitset<16>& ipPartDC
        );
        
        void calculerChecksum();
        void verifierChecksum();

        std::stack<std::bitset<16>> encapsuler(std::stack<std::bitset<16>>& segment);
        std::stack<std::bitset<16>> desencapsuler(std::stack<std::bitset<16>>& paquet);

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux, 
            const Internet& coucheInt
        );
};