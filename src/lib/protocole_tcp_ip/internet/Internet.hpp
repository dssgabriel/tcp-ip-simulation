/**
 * internet.hpp : Vous trouverez ici la classe Internet.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#ifndef internet_HPP
#define internet_HPP

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
        IPv4 m_IpSrc ;
        IPv4 m_IpDest ;
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
        IPv4& getIpSrc();

        void setIpDest(IPv4 dest);
        IPv4& getIpDest();

        void setTTL(const std::bitset<8>& ttl);
        std::bitset<8>& getTTL();

        void setProtocoleId();
        std::bitset<8>& getProtocoleId();
        
        // Methodes
        std::bitset<32> convertir(const IPv4& adresse);
        IPv4& convertir(
            const std::bitset<16>& ipPartBA, 
            const std::bitset<16>& ipPartDC
        );
        
        void calculerChecksum();
        void verifierChecksum();

        std::stack<std::bitset<16>> encapsuler(std::stack<std::bitset<16>>& segment);
        std::stack<std::bitset<16>> desencapsuler(std::stack<std::bitset<16>>& paquet);
};

#endif