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

struct MAC {
std::bitset<8> a;
std::bitset<8> b;
std::bitset<8> c;
std::bitset<8> d;
std::bitset<8> e;
std::bitset<8> f;
};

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
        std::bitset<48> convertirMacEnBits(const MAC& adresse);
        std::stack<std::bitset<16>> encapsuler(std::stack<std::bitset<16>>& paquet);
        std::stack<std::bitset<16>> desencapsuler(std::stack<std::bitset<16>>& trame);
};

#endif