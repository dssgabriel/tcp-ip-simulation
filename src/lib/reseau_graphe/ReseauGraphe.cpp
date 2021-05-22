#include <algorithm>
#include <cstdlib>

#include "ReseauGraphe.hpp"
#include "machine/Routeur.hpp"

std::vector<Machine*> ReseauGraphe::m_Machines;
std::vector<Liaison> ReseauGraphe::m_Liaisons;

ReseauGraphe::ReseauGraphe() {
    m_Machines.clear();
    m_Liaisons.clear();
}

ReseauGraphe::~ReseauGraphe() {}

// Getters & setters
void ReseauGraphe::setNom(const std::string nom) {
    m_Nom = nom;
}

const std::string& ReseauGraphe::getNom() const{
    return m_Nom;
}

uint8_t ReseauGraphe::getIdRouteurDepuisIdMachine(const uint16_t idMachine) {
    for (Machine* m: m_Machines) {
        if (m->getIdMachine() == idMachine) {
            Routeur* r = dynamic_cast<Routeur*>(m);

            if (r) {
                return r->getIdRouteur();
            } else {
                return 0;
            }
        }
    }

    std::cout << "ERREUR : methode `getIdRouteurDepuisIdMachine` : `"
        << idMachine << "` introuvable sur le reseau.\n";
    return 0;
}

Routeur* ReseauGraphe::getRouteur(const uint8_t idRouteur) {
    for (Machine* m: m_Machines) {
        Routeur* r= dynamic_cast<Routeur*>(m);

        if (r != nullptr && r->getIdRouteur() == idRouteur) {
            return r;
        }
    }

    std::cout << "ERREUR : methode `getRouteur` : `"
        << idRouteur << "` introuvable sur le reseau.\n";
    return nullptr;
}

Machine* ReseauGraphe::getMachine(const IPv4& ip) {
   for (Machine* m : m_Machines) {
       if (m->getIp() == ip) {
           return m;
       }
   }

    std::cout << "ERREUR : Dans le fichier 'ReseauGraphe.cpp'. ";
    std::cout << "Dans la fonction 'getMachine(ip)'. ";
    std::cout << "Adresse IP introuvable sur le reseau.\n";
    exit(EXIT_FAILURE);
}

Machine* ReseauGraphe::getMachine(const uint16_t& id) {
    if (id > m_Machines.size()) {
        std::cout << "ERREUR : Dans le fichier 'ReseauGraphe.cpp'. ";
        std::cout << "Dans la fonction 'getMachine(id)'. ";
        std::cout << "Indice en dehors du tableau.\n";
        exit(EXIT_FAILURE);
    }

    return m_Machines[id];
}

IPv4 ReseauGraphe::getSousReseau(const IPv4& ipMachine) {
    for (Machine* iter : m_Machines) {
        if (iter->getIp() == ipMachine) {
            return iter->getSousReseaux()[0];
        }
    }

    std::cout << "ERREUR : Dans le fichier 'ReseauGraphe.cpp'. ";
    std::cout << "Dans la fonction 'getSousReseau'. ";
    std::cout << "Aucune ipMachine trouvee.\n";
    exit(EXIT_FAILURE);
}

const std::vector<Machine*>& ReseauGraphe::getMachines() const {
    return m_Machines;
}

const std::vector<Liaison>& ReseauGraphe::getLiaisons() const {
    return m_Liaisons;
}

const std::vector<uint8_t> ReseauGraphe::getIdsRouteurs() {
    std::vector<uint8_t> idsRouteurs;

    for (Machine* iter: m_Machines) {
        Routeur* r = dynamic_cast<Routeur*>(iter);

        if (r) {
            idsRouteurs.emplace_back(r->getIdRouteur());
        }
    }

    return idsRouteurs;
}

// Overloading
std::ostream& operator<<(std::ostream& flux, const ReseauGraphe& reseau) {
    flux << "Nom du réseau : " << reseau.getNom() << "\n";

    // Affichage de la liste des machines.
    std::vector<Machine*> cpyMachines = reseau.getMachines();
    for (Machine* m : cpyMachines) {
        flux << *m << "\n";
    }

    // Affichage de la liste des liaisons.
    std::vector<Liaison> cpyLiaisons = reseau.getLiaisons();
    for (Liaison l : cpyLiaisons) {
        flux << l << "\n";
    }

    return flux;
}

// Methodes
bool ReseauGraphe::estConnexe() {
    return false;
}

void ReseauGraphe::ajouter(Machine* m) {
    m_Machines.emplace_back(m);
}

void ReseauGraphe::ajouter(Liaison l) {
    m_Liaisons.emplace_back(l);
}

uint8_t getIdRouteurPlusProche(std::vector<uint64_t>& sommeMetrique,
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

std::vector<Liaison> ReseauGraphe::getCheminsVoisins(const uint8_t& courant) {
    std::vector<Liaison> cheminsVoisins;

    for (Liaison chemin: m_Liaisons) {
        uint8_t r1 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine1);
        uint8_t r2 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine2);

        if (r1 == courant || r2 == courant) {
            cheminsVoisins.emplace_back(chemin);
        }
    }

    return cheminsVoisins;
}

void ReseauGraphe::getPlusCourtChemin(const uint8_t& depart,
                                      const uint8_t& arrivee,
                                      std::vector<int16_t> peres,
                                      std::vector<Liaison*> plusCourtChemin)
{
    uint8_t courant = arrivee;

    while (courant != depart) {
        uint8_t suivant = peres[courant - 1];

        Routeur* routeur1 = getRouteur(courant);
        Routeur* routeur2 = getRouteur(suivant);
        uint16_t idMachine1 = routeur1->getIdMachine();
        uint16_t idMachine2 = routeur2->getIdMachine();

        for (Liaison chemin: m_Liaisons) {
            if ((chemin.m_NumMachine1 == idMachine1 && chemin.m_NumMachine2 == idMachine2) ||
                (chemin.m_NumMachine1 == idMachine2 && chemin.m_NumMachine2 == idMachine1))
            {
                plusCourtChemin.emplace_back(&chemin);
            }
        }

        courant = suivant;
    }

    std::reverse(plusCourtChemin.begin(), plusCourtChemin.end());
}

std::vector<Liaison*> ReseauGraphe::routageDynamique(const uint8_t depart,
                                                     const uint8_t arrivee)
{
    std::vector<uint8_t> visites, nonVisites = getIdsRouteurs();
    std::vector<uint64_t> sommeMetrique(nonVisites.size(), UINT64_MAX);
    std::vector<int16_t> peres(nonVisites.size(), -1);
    std::vector<Liaison*> plusCourtChemin;

    sommeMetrique[depart - 1] = 0;

    for (size_t i = 0; i < nonVisites.size(); ++i) {
        nonVisites[i] = i + 1;
    }

    while (visites.size() < nonVisites.size()) {
        uint8_t courant = getIdRouteurPlusProche(sommeMetrique, visites, nonVisites);
        std::vector<Liaison> cheminsVoisins = getCheminsVoisins(courant);

        for (Liaison suivante: cheminsVoisins) {
            uint8_t r1 = getIdRouteurDepuisIdMachine(suivante.m_NumMachine1);
            uint8_t r2 = getIdRouteurDepuisIdMachine(suivante.m_NumMachine2);

            if (r1 != 0 && r1 == courant) {
                if (sommeMetrique[r2 - 1] > sommeMetrique[courant - 1] + suivante.m_Debit) {
                    sommeMetrique[r2 - 1] = sommeMetrique[courant - 1] + suivante.m_Debit;
                    peres[r2 - 1] = courant;
                }
            } else if (r2 != 0 && r2 == courant) {
                if (sommeMetrique[r1 - 1] > sommeMetrique[courant - 1] + suivante.m_Debit) {
                    sommeMetrique[r1 - 1] = sommeMetrique[courant - 1] + suivante.m_Debit;
                    peres[r1 - 1] = courant;
                }
            }
        }
    }

    getPlusCourtChemin(depart, arrivee, peres, plusCourtChemin);

    return plusCourtChemin;
}
