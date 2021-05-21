#include <algorithm>
#include <cstdlib>

#include "ReseauGraphe.hpp"
#include "machine/Routeur.hpp"

std::vector<Machine> ReseauGraphe::m_Machines;
std::vector<Liaison> ReseauGraphe::m_Liaisons;

ReseauGraphe::ReseauGraphe() {
    m_Machines.clear();
    m_Liaisons.clear();
}

ReseauGraphe::~ReseauGraphe() {
}

// Getters & setters
void ReseauGraphe::setNom(const std::string nom) {
    m_Nom = nom;
}

const std::string& ReseauGraphe::getNom() const{
    return m_Nom;
}

uint8_t ReseauGraphe::getIdRouteurDepuisIdMachine(const uint16_t idMachine) {
    for (auto iter: m_Machines) {
        Routeur& routeur = dynamic_cast<Routeur&>(iter);

        if (routeur.getIdMachine() == idMachine) {
            return routeur.getIdRouteur();
        }
    }

    std::cout << "ERREUR : Machine `" << idMachine << "` introuvable sur le reseau." << std::endl;
    exit(EXIT_FAILURE);
}

Routeur& ReseauGraphe::getRouteur(const uint8_t idRouteur) {
    for (size_t i = 0; i < m_Machines.size(); ++i) {
        Routeur& routeur = dynamic_cast<Routeur&>(m_Machines[i]);

        if (routeur.getIdRouteur() == idRouteur) {
            return dynamic_cast<Routeur&>(m_Machines[i]);
        }
    }

    std::cout << "ERREUR : Routeur `" << idRouteur << "` introuvable sur le reseau." << std::endl;
    exit(EXIT_FAILURE);
}

Machine& ReseauGraphe::getMachine(const IPv4& ip) {
   for (size_t i = 0; i < m_Machines.size(); ++i) {
       if (m_Machines[i].getIp() == ip) {
           return m_Machines[i];
       }
   }

    std::cout << "ERREUR : Dans la fonction 'getMachine' : Adresse IP <" << ip;
    std::cout << "> introuvable sur le reseau.\n";
    exit(EXIT_FAILURE);
}

Machine* ReseauGraphe::getMachine(const uint16_t& id) {
    if (id > m_Machines.size()) {
        std::cout << "ERREUR : Dans la fonction 'getMachine' :";
        std::cout << " Indice en dehors du tableau.\n";
        exit(EXIT_FAILURE);
    }

    return &m_Machines[id - 1];
}

const std::vector<Machine>& ReseauGraphe::getMachines() const {
    return m_Machines;
}

const std::vector<Liaison>& ReseauGraphe::getLiaisons() const {
    return m_Liaisons;
}

// Overloading
std::ostream& operator<<(std::ostream& flux, const ReseauGraphe& reseau) {
    flux << "Nom du réseau : " << reseau.getNom() << "\n";

    // Affichage de la liste des machines.
    std::vector<Machine> cpyMachines = reseau.getMachines();
    for(Machine m : cpyMachines) {
        flux << m << "\n";
    }

    // Affichage de la liste des liaisons.
    std::vector<Liaison> cpyLiaisons = reseau.getLiaisons();
    for(Liaison l : cpyLiaisons) {
        flux << l << "\n";
    }

    return flux;
}

// Methodes
bool ReseauGraphe::estConnexe() {
    return false;
}

void ReseauGraphe::ajouter(Machine m) {
    m_Machines.emplace_back(m);
}

void ReseauGraphe::ajouter(Liaison l) {
    m_Liaisons.emplace_back(l);
}

// TODO : Verifications
uint8_t getRouteurPlusProche(
    std::vector<uint64_t>& sommeMetrique,
    std::vector<uint8_t>& visites,
    std::vector<uint8_t>& nonVisites)
{
    uint64_t metriqueMinimale = UINT64_MAX;
    uint8_t idRouteurPlusProche;

    for (size_t i = 0; i < nonVisites.size(); ++i) {
        if (sommeMetrique[nonVisites[i]] < metriqueMinimale) {
            metriqueMinimale = sommeMetrique[nonVisites[i]];
            idRouteurPlusProche = nonVisites[i];
        }
    }

    nonVisites.erase(nonVisites.begin() + idRouteurPlusProche);
    visites.emplace_back(idRouteurPlusProche);

    return idRouteurPlusProche;
}

std::vector<Liaison> ReseauGraphe::getCheminsVoisins(const uint8_t& routeurCourant) {
    std::vector<Liaison> cheminsVoisins;

    for (auto chemin: m_Liaisons) {
        uint8_t routeur1 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine1);
        uint8_t routeur2 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine2);

        if (routeur1 == routeurCourant || routeur2 == routeurCourant) {
            cheminsVoisins.emplace_back(chemin);
        }
    }

    return cheminsVoisins;
}

void ReseauGraphe::getPlusCourtChemin(
    const uint8_t& depart,
    const uint8_t& arrivee,
    std::vector<int16_t> peres,
    std::vector<Liaison*> plusCourtChemin)
{
    uint8_t routeurCourant = arrivee;

    while (routeurCourant != depart) {
        uint8_t routeurSuivant = peres[routeurCourant - 1];
        Routeur routeur1 = getRouteur(routeurCourant);
        Routeur routeur2 = getRouteur(routeurSuivant);
        uint16_t idMachine1 = routeur1.getIdMachine();
        uint16_t idMachine2 = routeur2.getIdMachine();

        for (auto chemin: m_Liaisons) {
            if ((chemin.m_NumMachine1 == idMachine1 && chemin.m_NumMachine2 == idMachine2) ||
                (chemin.m_NumMachine1 == idMachine2 && chemin.m_NumMachine2 == idMachine1))
            {
                plusCourtChemin.emplace_back(&chemin);
            }
        }

        routeurCourant = routeurSuivant;
    }

    std::reverse(plusCourtChemin.begin(), plusCourtChemin.end());
}

std::vector<Liaison*> ReseauGraphe::routageDynamique(const uint8_t depart, const uint8_t arrivee) {
    std::vector<uint8_t> visites;
    std::vector<uint8_t> nonVisites(m_Machines.size(), 0);
    std::vector<uint64_t> sommeMetrique(m_Machines.size(), UINT64_MAX);
    std::vector<int16_t> peres(m_Machines.size(), -1);
    std::vector<Liaison*> plusCourtChemin;

    sommeMetrique[depart] = 0;

    for (size_t i = 0; i < m_Machines.size(); ++i) {
        nonVisites[i] = i + 1;
    }

    while (visites.size() < m_Machines.size()) {
        uint8_t routeurCourant = getRouteurPlusProche(sommeMetrique, visites, nonVisites) - 1;
        std::vector<Liaison> cheminsVoisins = getCheminsVoisins(routeurCourant);

        for (auto routeurSuivant: cheminsVoisins) {
            uint8_t routeur1 = getIdRouteurDepuisIdMachine(routeurSuivant.m_NumMachine1) - 1;
            uint8_t routeur2 = getIdRouteurDepuisIdMachine(routeurSuivant.m_NumMachine2) - 1;

            if (routeur1 == routeurCourant) {
                if (sommeMetrique[routeur2] > sommeMetrique[routeurCourant] + routeurSuivant.m_Debit) {
                    sommeMetrique[routeur2] = sommeMetrique[routeurCourant] + routeurSuivant.m_Debit;
                    peres[routeur2] = routeurCourant;
                }
            } else if (routeur2 == routeurCourant) {
                if (sommeMetrique[routeur1] > sommeMetrique[routeurCourant] + routeurSuivant.m_Debit) {
                    sommeMetrique[routeur1] = sommeMetrique[routeurCourant] + routeurSuivant.m_Debit;
                    peres[routeur1] = routeurCourant;
                }
            }
        }
    }

    getPlusCourtChemin(depart, arrivee, peres, plusCourtChemin);

    return plusCourtChemin;
}
