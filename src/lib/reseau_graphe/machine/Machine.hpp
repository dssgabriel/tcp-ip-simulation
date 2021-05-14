#pragma once

#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <iostream>

#include "../../../include/MAC.hpp"
#include "../../../include/IPv4.hpp"
#include "../../horloge/Horloge.hpp"
#include "../../../include/Commun.hpp"
#include "../../protocole_tcp_ip/internet/Internet.hpp"
#include "../../protocole_tcp_ip/physique/Physique.hpp"

class Machine {
    private:
        // Attributs prives
        static uint16_t m_NbMachine;
        uint16_t m_IdMachine;
    
    protected:
        // Attributs proteges
        std::string m_Nom;
        
        IPv4 m_Ip;
        MAC m_Mac;
        IPv4 m_Masque;
        std::vector<IPv4> m_SousReseau;
        
        // Horloge m_Chrono;
        std::vector<Machine*> m_Voisins;
        std::queue<std::stack<std::bitset<16>>*> m_FileDonnees;
    
    public:
        // Constructeur
        Machine();
        
        // Destructeur
        virtual ~Machine() {};
        
        // Getters & setters
        const uint16_t& getNbMachine() const;
        const uint16_t& getIdMachine() const;
        
        void setNom(const std::string& nom);
        const std::string& getNom() const;
        
        void setIp(const IPv4& ip);
        const IPv4& getIp() const;
        
        void setMasque(const IPv4& masque);
        const IPv4& getMasque() const;
        
        void setMac(const MAC& mac);
        const MAC& getMac() const;
        
        void setSousReseau(const IPv4& sousReseau);
        const std::vector<IPv4>& getSousReseau() const;
        
        void setVoisin(Machine& voisin);
        Machine* getVoisin(MAC adresseVoisin);

        void setDonnee(std::stack<std::bitset<16>>* donnee);
        std::stack<std::bitset<16>>* suppDonnee();

        const std::queue<std::stack<std::bitset<16>>*>& getDonnees();

        // Methodes
        virtual void recevoir() {};

        // NE PAS NOMMER LES VARIABLES.
        virtual void envoyer(const uint32_t) {};
        virtual void traitement(std::stack<std::bitset<16>>&, MAC) {};

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux, 
            const Machine& machine
        );
};