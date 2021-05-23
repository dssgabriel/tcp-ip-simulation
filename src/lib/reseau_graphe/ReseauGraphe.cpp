/**
 * @file    ReseauGraphe.cpp
 * @brief   Vous trouverez ici toutes les fonctions implementees pour la classe ReseauGraphe.
 * @author  Florian CAMBRESY
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 **/

#include <algorithm>
#include <cstdlib>
#include <omp.h>

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

const std::string& ReseauGraphe::getNom() const{
    return m_Nom;
}

uint8_t ReseauGraphe::getIdRouteurDepuisIdMachine(const uint16_t idMachine) {
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

Routeur* ReseauGraphe::getRouteur(const uint8_t idRouteur) {
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
    uint8_t idRouteurPlusProche = 0;

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
        std::cout << "Log #0: `getCheminVoisin`" << std::endl;
        uint8_t r1 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine1);
        std::cout << "Log #1: `getCheminVoisin`" << std::endl;
        uint8_t r2 = getIdRouteurDepuisIdMachine(chemin.m_NumMachine2);
        std::cout << "Log #2: `getCheminVoisin`" << std::endl;

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
            std::cout << "Log #0: `routageDynamique`" << std::endl;
            uint8_t r1 = getIdRouteurDepuisIdMachine(suivante.m_NumMachine1);
            std::cout << "Log #1: `routageDynamique`" << std::endl;
            uint8_t r2 = getIdRouteurDepuisIdMachine(suivante.m_NumMachine2);
            std::cout << "Log #2: `routageDynamique`" << std::endl;

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

void ReseauGraphe::lancerOSPF() {
    for (Machine* machine: m_Machines) {
        std::cout << "log #0 : avant for machine\n";
        Routeur* routeur = dynamic_cast<Routeur*>(machine);

        if (routeur) {
            std::cout << "\tlog #1 : avant if routeur\n";
            std::vector<Machine*> voisins = routeur->getVoisins();

            #pragma omp parallel for
            for (Machine* voisin: voisins) {
                std::cout << "\t\tlog #2 : avant for voisine\n";
                Routeur* routeurVoisin = dynamic_cast<Routeur*>(voisin);

                if (routeurVoisin) {
                    std::cout << "\t\t\tlog #3 : avant if voisin\n";
                    PaquetHello* hello = new PaquetHello(routeurVoisin->getIdRouteur());
                    hello->setEntete(Hello, routeur->getIdRouteur());
                    std::cout << "\t\t\tlog #3.5 : avant envoyerOSPF\n"
                        << "envoyerOSPF(" << routeurVoisin->getIp()
                        << ", hello)\n"
                        << "############################################\n";
                    routeur->envoyerOSPF(routeurVoisin, hello);
                    std::cout << "\t\t\tlog #3.5 : apres envoyerOSPF\n"
                        << "############################################\n";
                    std::cout << "\t\t\tlog #3 : apres if voisin\n";
                }
                std::cout << "\t\tlog #2 : apres for voisine\n";
            }
            std::cout << "\tlog #1 : apres if routeur\n";
        }
        std::cout << "log #0 : apres for machine\n";
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