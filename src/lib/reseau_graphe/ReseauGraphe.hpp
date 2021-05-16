#pragma once

#include <vector>
#include <string>

#include "machine/Machine.hpp"
#include "machine/Routeur.hpp"
#include "machine/Commutateur.hpp"
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
        const std::string& getNom() const;

        Machine& getMachine(const IPv4& ip);
        Machine* getMachine(const unsigned int& indice);
        const std::vector<Machine>& getMachines() const;

        const std::vector<Liaison>& getLiaisons() const;

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux, 
            const ReseauGraphe& reseau
        );

        // Methodes
        bool estConnexe();

        void ajouter(Machine m);
        void ajouter(Liaison l);

        void routageDynamique();
};
