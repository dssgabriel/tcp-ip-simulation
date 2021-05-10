#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "../../include/ParamInterface.hpp"
#include "../reseau_graphe/ReseauGraphe.hpp"
#include "../../include/json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

std::unique_ptr<ReseauGraphe> chargerReseau(const std::string& nomFichier) {
    // Initialisation.
    ReseauGraphe reseau;
    
    // Lecture du fichier.
    std::ifstream lecture("file.json");
    json j;
    lecture >> j;

    reseau.setNom(j["Nom du reseau"]);
}

void chargerConfig(const std::string& cheminFichier,
    std::unique_ptr<ReseauGraphe>& reseau, ParamInterface& param)
{

}