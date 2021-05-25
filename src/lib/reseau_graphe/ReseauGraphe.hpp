/**
 * @file    ReseauGraphe.hpp
 * @brief   Vous trouverez ici la declaration de la classe ReseauGraphe
 * @author  Florian Cambresy
 * @author  Gabriel Dos Santos
 * @author  Mickael Le Denmat
 * @date    Mai 2021
 **/

#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "machine/Machine.hpp"
#include "machine/Routeur.hpp"
#include "machine/Commutateur.hpp"
#include "../../include/Liaison.hpp"

class ReseauGraphe {
    private:
        // Attributs
        std::string m_Nom;
        static std::vector<Machine*> m_Machines;
        static std::vector<Liaison> m_Liaisons;

        // Methodes privees
        static uint16_t getRouteur(const uint16_t& idMachine);
        static std::vector<Liaison> getCheminsVoisins(const uint16_t& routeurCourant);
        static void getPlusCourtChemin(
            const uint16_t& depart,
            const uint16_t& arrivee,
            std::vector<uint16_t>& peres,
            std::vector<Liaison*>& plusCourtChemin
        );

    public:
        // Constructeur
        ReseauGraphe();

        // Destructeur
        ~ReseauGraphe();

        // Getters & setters
        void remettreIdAZero();

        void setNom(const std::string nom);
        const std::string& getNom() const;

        static Routeur* getPtrRouteur(const uint16_t& idRouteur);
        static uint16_t getIdRouteurDepuisIdMachine(const uint16_t& idMachine);

        static Machine* getMachine(const IPv4& ip);
        Machine* getMachine(const uint16_t& id);

        static IPv4 getSousReseau(const IPv4& ipMachine);

        const std::vector<Machine*>& getMachines() const;

        const std::vector<Liaison>& getLiaisons() const;

        static const std::vector<uint16_t> getIdsRouteurs();

        const std::map<uint32_t, double> getTempsPaquet() const;

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux,
            const ReseauGraphe& reseau
        );

        // Methodes
        static bool estRouteur(const uint16_t& idMachine);
        bool estConnexe();

        void ajouter(Machine* m);
        void ajouter(Liaison l);

        void lancerOSPF();
        static std::vector<Liaison*> routageDynamique(
            const uint16_t& depart, const uint16_t& arrivee
        );
};
