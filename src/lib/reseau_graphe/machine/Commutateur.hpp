#pragma once

#include <map>
#include "Machine.hpp"

class Commutateur : public Machine {
    private:
        // Attributs
        static uint8_t m_NbrCommutateur;
        uint8_t m_IdCommutateur;
        std::map<const IPv4*, const MAC*> m_CacheMem;
    	
    public:
        // Constructeurs
        Commutateur();
        
        // Destructeur
        ~Commutateur();
        
        // Getters
        uint8_t getNbrCommutateur();
        uint8_t getIdCommutateur();
        void setMemoire(const IPv4* ip, const MAC* mac);
        const std::map<const IPv4*, const MAC*>& getMemoire() const;
        
        // Methode
        virtual void envoyer(const uint32_t cwnd, const bool isAck);
        virtual void recevoir(const uint32_t cwnd, const bool isAck);
        MAC trouverMacDest(const IPv4 ip);

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux, 
            Commutateur& c
        );
};