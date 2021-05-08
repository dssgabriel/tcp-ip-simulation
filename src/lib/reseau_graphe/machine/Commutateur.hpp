#pragma once

#include <map>

#include "Machine.hpp"
#include "../../protocole_tcp_ip/internet/Internet.hpp"

class Commutateur : public Machine {
    private:
        // Attributs
        static uint8_t m_NbrCommutateur;
        uint8_t m_IdCommutateur;
        std::map<IPv4, MAC> m_CacheMem;
    	
    public:
        // Constructeurs
        Commutateur();
        // // Commutateur(const std::string& nom);
        
        // Destructeur
        ~Commutateur();
        
        // Getters
        uint8_t getNbrCommutateur();
        uint8_t getIdCommutateur();
        
        // Methode
        void envoyer();
        void recevoir();
        void traitement(std::stack<std::bitset<16>> &donnee, MAC nouvelleDest);
        MAC trouverMacDest(const IPv4& ip);
};