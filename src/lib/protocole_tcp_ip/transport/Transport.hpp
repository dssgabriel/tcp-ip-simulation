/**
 * @file        Transport.hpp
 * @brief       Déclaration de la classe Transport.
 * 
 * @author      Quentin GRUCHET 
 * @author      Fadi MECHRI
 * @date        2021
 **/

#ifndef transport_HPP
#define transport_HPP

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <stack>
#include <time.h>

#include "../../../include/Commun.hpp"
#include "../../../include/ParamInterface.hpp"

class Transport {
    private :
       
        // Attributs
        uint16_t m_PortSrc;
        uint16_t m_PortDest;
        std::bitset<16> m_Cwnd;
        std::bitset<16> m_Checksum;
        std::bitset<16> m_Syn;
        std::bitset<16> m_Ack1;
        std::bitset<32> m_Seq;
        std::bitset<32> m_Ack2;
  
    public :
       
        // Constructeur
        Transport();
    
        // Destructeur
        ~Transport();
    
        // Setters & getters
        void setPortSrc(const uint16_t & src);
        const uint16_t & getPortSrc() const;

        void setPortDest(TypeFichier num);
        const uint16_t & getPortDest() const;
        
        void setCwnd(const std::bitset<16>& cwnd);
        const std::bitset<16>& getCwnd() const;
        
        void setChecksum(const std::bitset<16>& checksum);
        const std::bitset<16>& getChecksum() const;
        
        void setSyn(const std::bitset<16>& syn);
        const std::bitset<16>& getSyn() const;
        
        void setAck1(const std::bitset<16>& ack1);
        const std::bitset<16>& getAck1() const;
        
        void setSeq(const std::bitset<32>& numSeq);
        const std::bitset<32>& getSeq() const;
        
        void setAck2(const std::bitset<32>& ack2);
        const std::bitset<32>& getAck2() const;

        // Methodes
        uint16_t portAlea();

        void calculerChecksum();
        void verifierChecksum();
        
        std::stack<std::bitset<16>> encapsuler(std::bitset<16> donnee);
        std::bitset<16> desencapsuler(std::stack<std::bitset<16>>& segment);

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux, 
            const Transport& coucheTrans
        );
};

#endif