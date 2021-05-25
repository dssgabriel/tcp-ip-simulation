/**
 * @file Machine.hpp
 * @author Mickael LE DENMAT
 * @brief Vous trouverez ici la definition de la classe Machine.
 * @date 2021-05-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

// Import des librairies deja definies.
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <bitset>
#include <string>
#include <iostream>

// Import des librairies exterieures.
#include "../../../include/MAC.hpp"
#include "../../../include/IPv4.hpp"
#include "../../horloge/Horloge.hpp"
#include "../../../include/Commun.hpp"
#include "../../protocole_tcp_ip/internet/Internet.hpp"
#include "../../protocole_tcp_ip/physique/Physique.hpp"
#include "../../protocole_tcp_ip/transport/Transport.hpp"

/**
 * @brief Classe Machine qui represente tout objet present sur le reseau.
 * 
 */
class Machine {
    private:
        static uint16_t m_NbMachine;
        uint16_t m_IdMachine;

    protected:
        std::string m_Nom;

        IPv4 m_Ip;
        MAC m_Mac;
        IPv4 m_Masque;
        std::vector<IPv4> m_SousReseau;

        Horloge m_Chrono;
        std::vector<Machine*> m_Voisins;
        std::deque<std::stack<std::bitset<16>>> m_FileDonnees;
        std::map<uint32_t, double> m_TempsTraitementPaquet;
    
    public:
        // Constructeur
        Machine();

        // Destructeur
       virtual ~Machine();

        // Getters & setters
        const uint16_t& getNbMachine() const;
        const uint16_t& getIdMachine() const;
        inline void remettreIdAZero() { m_IdMachine = 0; }

        void setNom(const std::string& nom);
        const std::string& getNom() const;

        void setIp(const IPv4& ip);
        const IPv4& getIp() const;

        void setMasque(const IPv4& masque);
        const IPv4& getMasque() const;

        void setMac(const MAC& mac);
        const MAC& getMac() const;

        void setSousReseau(const IPv4& sousReseau);
        const std::vector<IPv4>& getSousReseaux() const;

        void setVoisin(Machine& voisin);
        Machine* getVoisin(MAC adresseVoisin) const;
        std::vector<Machine*> getVoisins() const;

        void setDonnee(const std::stack<std::bitset<16>>& trame);
        std::stack<std::bitset<16>> suppDonnee();

        std::deque<std::stack<std::bitset<16>>>& getDonnees();

        const double& getTempsTraitementPaquet(const uint32_t& numPaquet) const;
        const std::map<uint32_t, double>& getTempsTraitementPaquets() const;

        // Methodes
        // NE PAS NOMMER LES VARIABLES.
        virtual void envoyer(const uint32_t, bool) {}
        void traitement(std::stack<std::bitset<16>>&, MAC);
        virtual void recevoir(const uint32_t, bool) {}

        void lancerHorloge();
        void arreterHorloge();

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux, 
            const Machine& machine
        );
};
