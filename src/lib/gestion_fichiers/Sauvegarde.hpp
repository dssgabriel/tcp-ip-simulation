/**
 * @file Sauvegarde.hpp
 * @author Mickael Le Denmat
 * @brief Vous trouverez ici la declaration des fonctions de sauvegarde
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "../../include/ParamInterface.hpp"
#include "../../include/json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

void sauvegarderConfig(const std::string& cheminFichier,
    const std::string& nom, ParamInterface& param);
