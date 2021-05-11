#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "../../include/MAC.hpp"
#include "../../include/IPv4.hpp"
#include "../../include/Liaison.hpp"
#include "../../include/ParamInterface.hpp"
#include "../reseau_graphe/ReseauGraphe.hpp"
#include "../reseau_graphe/machine/Machine.hpp"
#include "../reseau_graphe/machine/Routeur.hpp"
#include "../reseau_graphe/machine/Ordinateur.hpp"
#include "../reseau_graphe/machine/Commutateur.hpp"
#include "../../include/json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

std::unique_ptr<ReseauGraphe> chargerReseau(const std::string& nomFichier) {
    // Initialisation du reseau.
    ReseauGraphe* reseau = new ReseauGraphe();
    if(!reseau) {
        std::cout << "ERREUR : Dans la fonction 'chargerReseau' : pointeur nul.\n";
        std::unique_ptr<ReseauGraphe>(nullptr); 
    }
    
    // Lecture du fichier.
    std::ifstream lecture(nomFichier);
    if(lecture.fail()) {
        std::cout << "ERREUR : Dans la fonction 'chargerReseau' : Fichier JSON introuvable.\n";
        exit(EXIT_FAILURE);
    }

    // Convertion du fichier en JSON.
    json j;
    lecture >> j;

    // Remplissage du reseau.
    reseau->setNom(j["Nom du reseau"]);
    
    // Remplissage de la liste des machines.
    auto listeMachineJ = j["Liste machines"];
    for(auto machineJ : listeMachineJ) {

        // Initialisation du type de machine.
        Machine* m;
        if(machineJ["type"] == "Ordinateur") {
            m = new Ordinateur();
        }
        else if(machineJ["type"] == "Routeur") {
            m = new Routeur();
        }
        else if(machineJ["type"] == "Commutateur") {
            m = new Commutateur();

            // Information supplementaire pour un routeur.
        }
        else {
            std::cout << "ERREUR : Dans la fonction 'chargerReseau' : Type de machine inconnu\n.";
            exit(EXIT_FAILURE);
        }
            
        // Initialisation des attributs la machine.
        IPv4 ip;
        ip.a = std::bitset<8>(machineJ["ip"][0]);
        ip.b = std::bitset<8>(machineJ["ip"][1]);
        ip.c = std::bitset<8>(machineJ["ip"][2]);
        ip.d = std::bitset<8>(machineJ["ip"][3]);
        m->setIp(ip);

        MAC mac;
        mac.a = std::bitset<8>(machineJ["mac"][0]);
        mac.b = std::bitset<8>(machineJ["mac"][1]);
        mac.c = std::bitset<8>(machineJ["mac"][2]);
        mac.d = std::bitset<8>(machineJ["mac"][3]);
        mac.e = std::bitset<8>(machineJ["mac"][4]);
        mac.f = std::bitset<8>(machineJ["mac"][5]);
        m->setMac(mac);

        ip.a = std::bitset<8>(machineJ["masque"][0]);
        ip.b = std::bitset<8>(machineJ["masque"][1]);
        ip.c = std::bitset<8>(machineJ["masque"][2]);
        ip.d = std::bitset<8>(machineJ["masque"][3]);
        m->setMasque(ip);

        for(auto sousReseauJ : machineJ["sous reseaux"]) {
            ip.a = std::bitset<8>(sousReseauJ[0]);
            ip.b = std::bitset<8>(sousReseauJ[1]);
            ip.c = std::bitset<8>(sousReseauJ[2]);
            ip.d = std::bitset<8>(sousReseauJ[3]);
            m->setSousReseau(ip);
        }

        // Ajout de la machine creee dans le reseau.
        reseau->ajouter(*m);
    }

    // Remplissage de la liste des liaisons.
    auto listeLiaisonsJ = j["Liste liaisons"];
    for(auto liaisonJ : listeLiaisonsJ) {
        Liaison l;
        l.m_NumMachine1 = liaisonJ["Depart"];
        l.m_NumMachine2 = liaisonJ["Arrivee"];
        l.m_Debit = liaisonJ["Debit"];

        // Ajout de la liaison dans le reseau.
        reseau->ajouter(l);
    }

    // Convertion.
    return std::unique_ptr<ReseauGraphe>(reseau);
}

void chargerConfig(const std::string& cheminFichier,
    std::unique_ptr<ReseauGraphe>& reseau, ParamInterface& param)
{
    // Lecture du fichier.
    std::ifstream lecture(cheminFichier);
    if(lecture.fail()) {
        std::cout << "ERREUR : Dans la fonction 'chargerConfig' : Fichier JSON introuvable.\n";
        exit(EXIT_FAILURE);
    }

    // Convertion du fichier en JSON.
    json j;
    lecture >> j;

    // Chargement des parametres.
    IPv4 ip;
    ip.a = std::bitset<8>(j["IP destination"][0]);
    ip.b = std::bitset<8>(j["IP destination"][1]);
    ip.c = std::bitset<8>(j["IP destination"][2]);
    ip.d = std::bitset<8>(j["IP destination"][3]);
    param.m_Destination = ip;

    ip.a = std::bitset<8>(j["IP source"][0]);
    ip.b = std::bitset<8>(j["IP source"][1]);
    ip.c = std::bitset<8>(j["IP source"][2]);
    ip.d = std::bitset<8>(j["IP source"][3]);
    param.m_Source = ip;

    param.m_NbPaquet = j["Nombre de paquets"];
    param.m_Ssthresh = j["ssthresh"];
    param.m_TypeFichier = j["Type de fichier"];

    // Chargement du reseau.
    std::string choixReseau = j["Nom du reseau"];
    if(choixReseau == "ReseauSimple") {
        reseau = chargerReseau("../../include/ConfigReseau/ReseauSimple.json");
    }
    else if(choixReseau == "ReseauMaison") {
        reseau = chargerReseau("../../include/ConfigReseau/ReseauMaison.json");
    }
    else if(choixReseau == "ReseauPme") {
        reseau = chargerReseau("../../include/ConfigReseau/ReseauPme.json");
    }
    else if(choixReseau == "ReseauEntreprise") {
        reseau = chargerReseau("../../include/ConfigReseau/ReseauEntreprise.json");
    }
    else { 
        std::cout << "ERREUR : Dans la fonction 'chargerConfig' : Reseau choisi inconnu.\n";
    }
}