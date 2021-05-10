#pragma once

#include <vector>
#include <string>

#include "machine/Machine.hpp"
#include "../../include/Liaison.hpp"

class ReseauGraphe {
    private:
        // Attributs
        std::string m_Nom;
        std::vector<Machine> m_Machines;
        std::vector<Liaison> m_Liaisons;

    public:
        // Constructeur
        ReseauGraphe();

        // Destructeur
        ~ReseauGraphe();
    
        // Getters & setters
        void setNom(const std::string nom);
        std::string& getNom();
        
        Machine& getMachine(const IPv4& ip);
        
        // Methodes
        bool estConnexe();
        
        void ajouter(Machine m);
        void ajouter(Liaison l);
        
        void routageDynamique();
};