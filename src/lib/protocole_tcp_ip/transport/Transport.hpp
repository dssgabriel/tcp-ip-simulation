/**
 * Transport.hpp : Vous trouverez ici la classe Transport.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
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
        uint16_t m_PortSrc ;
        uint16_t m_PortDest ;
        std::bitset<16> m_Cwnd ;
        std::bitset<16> m_Checksum ;
        std::bitset<16> m_Syn ;
        std::bitset<16> m_Ack1 ;
        std::bitset<32> m_Seq ;
        std::bitset<32> m_Ack2 ;
  
    public :
       
        // Constructeur
        Transport();
    
        // Destructeur
        ~Transport();
    
        // Setters & getters
        void setPortSrc(const uint16_t & src);
        uint16_t & getPortSrc();

        void setPortDest(TypeFichier num) ;
        uint16_t & getPortDest();
        
        void setCwnd(const std::bitset<16>& cwnd);
        std::bitset<16>& getCwnd();
        
        void setChecksum(const std::bitset<16>& checksum);
        std::bitset<16>& getChecksum();
        
        void setSyn(const std::bitset<16>& syn);
        std::bitset<16>& getSyn();
        
        void setAck1(const std::bitset<16>& ack1);
        std::bitset<16>& getAck1();
        
        void setSeq(const std::bitset<32>& numSeq);
        std::bitset<32>& getSeq();
        
        void setAck2(const std::bitset<32>& ack2) ;
        std::bitset<32>& getAck2();

        // Methodes
        uint16_t portAlea() ;
        std::bitset<16> convertir(const uint16_t &);

        void calculerChecksum();
        void verifierChecksum();
        
        std::stack<std::bitset<16>> encapsuler();
        std::bitset<16> desencapsuler(std::stack<std::bitset<16>>& segment);
};

#endif