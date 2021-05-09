/**
 * physique.hpp : Vous pouvez trouver ici la classe Physique.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#ifndef physique_HPP
#define physique_HPP

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <stack>

#include "../../../include/MAC.hpp"
#include "../../../include/Commun.hpp"

class Physique {
    private :
        // Attributs
        MAC m_SrcMac;
        MAC m_DestMac;

    public :
       
        // Constructeur
        Physique();
       
        // Destructeur
        ~Physique();
       
        // Getters & setters
        MAC getMacSrc();
        void setMacSrc(MAC src);
        
        MAC getMacDest();
        void setMacDest(MAC dest);
        
        // Methodes
        MAC convetirBitsEnMac(
            const std::bitset<16>& adrPartAB, 
            const std::bitset<16>& adrPartCD,
            const std::bitset<16>& adrPartEF    
        );
        std::bitset<48> convertirMacEnBits(const MAC& adresse);
        std::stack<std::bitset<16>> decoupageMac(const std::bitset<48>& adresse);
        
        std::stack<std::bitset<16>> encapsuler(std::stack<std::bitset<16>>& paquet);
        std::stack<std::bitset<16>> desencapsuler(std::stack<std::bitset<16>>& trame);
};

#endif