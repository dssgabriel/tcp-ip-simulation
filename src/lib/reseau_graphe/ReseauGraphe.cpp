/**
 * @file    ReseauGraphe.cpp
 * @brief   Vous trouverez ici toutes les fonctions implementees pour la classe ReseauGraphe.
 * @author  Florian CAMBRESY
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 **/

#include <algorithm>
#include <cstdlib>
// #include <omp.h>

#include "ReseauGraphe.hpp"

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

const std::string& ReseauGraphe::getNom() const {
    return m_Nom;
}

uint16_t ReseauGraphe::getIdRouteurDepuisIdMachine(const uint16_t& idMachine) {
    for (Machine* m: m_Machines) {
        if (m->getIdMachine() == idMachine) {
            Routeur* r = dynamic_cast<Routeur*>(m);

            if (r != nullptr) {
                return r->getIdRouteur();
            }
        }
    }

    std::cout << "ERREUR : fichier `ReseauGraphe.cpp`\n"
        << "\tmethode `getIdRouteurDepuisIdMachine` : #"
        << idMachine << " introuvable sur le reseau"
        << std::endl;
    return 0;
}

Routeur* ReseauGraphe::getPtrRouteur(const uint16_t& idRouteur) {
    for (Machine* m: m_Machines) {
        Routeur* r= dynamic_cast<Routeur*>(m);

        if (r != nullptr && r->getIdRouteur() == idRouteur) {
            return r;
        }
    }

    std::cout << "ERREUR : fichier `ReseauGraphe.cpp`\n"
        << "\tmethode `getRouteur` : #"
        << idRouteur << " introuvable sur le reseau.\n";
    return nullptr;
}

Machine* ReseauGraphe::getMachine(const IPv4& ip) {
   for (Machine* m : m_Machines) {
       if (m->getIp() == ip) {
           return m;
       }
   }

    std::cout << "ERREUR : Dans le fichier 'ReseauGraphe.cpp'. "
        << "Dans la fonction 'getMachine(ip)'. "
        << "Adresse IP introuvable sur le reseau.\n";
    exit(EXIT_FAILURE);
}

Machine* ReseauGraphe::getMachine(const uint16_t& id) {
    if (id > m_Machines.size()) {
        std::cout << "ERREUR : Dans le fichier 'ReseauGraphe.cpp'. "
            << "Dans la fonction 'getMachine(id)'. "
            << "Indice en dehors du tableau.\n";
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

    std::cout << "ERREUR : Dans le fichier 'ReseauGraphe.cpp'. "
        << "Dans la fonction 'getSousReseau'. "
        << "Aucune ipMachine trouvee.\n";
    exit(EXIT_FAILURE);
}

const std::vector<Machine*>& ReseauGraphe::getMachines() const {
    return m_Machines;
}

const std::vector<Liaison>& ReseauGraphe::getLiaisons() const {
    return m_Liaisons;
}

const std::vector<uint16_t> ReseauGraphe::getIdsRouteurs() {
    std::vector<uint16_t> idsRouteurs;

    for (Machine* iter: m_Machines) {
        Routeur* r = dynamic_cast<Routeur*>(iter);

        if (r) {
            idsRouteurs.emplace_back(r->getIdRouteur());
        }
    }

    return idsRouteurs;
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
                               std::vector<uint16_t>& visites,
                               std::vector<uint16_t>& nonVisites)
{
    uint64_t metriqueMinimale = 0;
    uint16_t idRouteurPlusProche = 0;

    for (size_t i = 0; i < nonVisites.size(); ++i) {
        if (sommeMetrique[nonVisites[i]] > metriqueMinimale) {
            metriqueMinimale = sommeMetrique[nonVisites[i]];
            idRouteurPlusProche = nonVisites[i];
        }
    }

    nonVisites.erase(nonVisites.begin() + idRouteurPlusProche);
    visites.emplace_back(idRouteurPlusProche);

    return idRouteurPlusProche;
}

std::vector<Liaison> ReseauGraphe::getCheminsVoisins(const uint16_t& courant) {
    std::vector<Liaison> cheminsVoisins;

    for (Liaison chemin: m_Liaisons) {
        uint16_t r1 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine1);
        uint16_t r2 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine2);

        if (r1 == courant || r2 == courant) {
            cheminsVoisins.emplace_back(chemin);
        }
    }

    return cheminsVoisins;
}

void ReseauGraphe::getPlusCourtChemin(const uint16_t& depart,
                                      const uint16_t& arrivee,
                                      std::vector<int32_t> peres,
                                      std::vector<Liaison*> plusCourtChemin)
{
    uint16_t courant = arrivee;

    while (courant != depart) {
        uint16_t suivant = peres[courant - 1];

        Routeur* routeur1 = getPtrRouteur(courant);
        Routeur* routeur2 = getPtrRouteur(suivant);
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

std::vector<Liaison*> ReseauGraphe::routageDynamique(const uint16_t& depart,
                                                     const uint16_t& arrivee)
{
    std::vector<uint16_t> visites, nonVisites = getIdsRouteurs();
    std::vector<uint64_t> sommeMetrique(nonVisites.size(), UINT64_MAX);
    std::vector<int32_t> peres(nonVisites.size(), -1);
    std::vector<Liaison*> plusCourtChemin;

    sommeMetrique[depart - 1] = 0;

    for (size_t i = 0; i < nonVisites.size(); ++i) {
        nonVisites[i] = i + 1;
    }

    while (visites.size() < nonVisites.size()) {
        uint16_t courant = getIdRouteurPlusProche(sommeMetrique, visites, nonVisites);
        std::vector<Liaison> cheminsVoisins = getCheminsVoisins(courant);

        for (Liaison suivante: cheminsVoisins) {
            uint16_t r1 = getIdRouteurDepuisIdMachine(suivante.m_NumMachine1);
            uint16_t r2 = getIdRouteurDepuisIdMachine(suivante.m_NumMachine2);

            if (r1 != 0 && r1 == courant) {
                if (sommeMetrique[r2 - 1] < sommeMetrique[courant - 1] + suivante.m_Debit) {
                    sommeMetrique[r2 - 1] = sommeMetrique[courant - 1] + suivante.m_Debit;
                    peres[r2 - 1] = courant;
                }
            } else if (r2 != 0 && r2 == courant) {
                if (sommeMetrique[r1 - 1] < sommeMetrique[courant - 1] + suivante.m_Debit) {
                    sommeMetrique[r1 - 1] = sommeMetrique[courant - 1] + suivante.m_Debit;
                    peres[r1 - 1] = courant;
                }
            }
        }
    }

    getPlusCourtChemin(depart, arrivee, peres, plusCourtChemin);

    return plusCourtChemin;
}

void ReseauGraphe::lancerOSPF() {
    size_t c1 = 0, c2 = 0;
    for (Machine* machine: m_Machines) {
        Routeur* routeur = dynamic_cast<Routeur*>(machine);

        if (routeur) {
            std::vector<Machine*> voisins = routeur->getVoisins();
            c1++; std::cout << "Router #" << c1 << std::endl;

            // #pragma omp parallel for
            for (Machine* voisin: voisins) {
                Routeur* routeurVoisin = dynamic_cast<Routeur*>(voisin);

                if (routeurVoisin) {
                    c2++; std::cout << "Neighboor Router #" << c2 << std::endl;
                    PaquetOSPF* hello = new PaquetHello(routeurVoisin->getIdRouteur());
                    hello->setEntete(Hello, routeur->getIdRouteur());
                    routeur->envoyerOSPF(routeurVoisin, hello);
                }
            }
        }
    }
}

// Overloading
std::ostream& operator<<(std::ostream& flux, const ReseauGraphe& reseau) {
    flux << "Nom du réseau : " << reseau.getNom() << "\n";

    // Affichage de la liste des machines.
    for (Machine* m : reseau.getMachines()) {
        if (Routeur* r = dynamic_cast<Routeur*> (m)) {
            flux << *r << "\n";
        } else if (Commutateur* c = dynamic_cast<Commutateur*> (m)) {
            flux << *c << "\n";
        } else if (Ordinateur* o = dynamic_cast<Ordinateur*> (m)) {
            flux << *o << "\n";
        } else {
            flux << *m << "\n";
        }
    }

    return flux;
}
