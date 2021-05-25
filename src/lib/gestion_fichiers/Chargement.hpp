/**
 * @file Chargement.hpp
 * @author Mickael Le Denmat
 * @brief Vous trouverez ici la declaration des fonctions de chargement
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <array>
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

std::unique_ptr<ReseauGraphe> chargerReseau(const std::string& nomFichier);

void chargerConfig(const std::string& cheminFichier,
    std::unique_ptr<ReseauGraphe>& reseau, ParamInterface& param);
