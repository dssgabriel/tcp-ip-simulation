#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "../../include/ParamInterface.hpp"
#include "../../include/json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

/**
 * @brief Sauvegarde la configuration rentre par l'utilisateur.
 *  
 * @param cheminFichier : L'emplacement de sauvegarde du fichier.
 * @param nom : Nom de la sauvegarde.
 * @param param : La configuration a auvegarder.
 */
void sauvegarderConfig(const std::string& cheminFichier,
    const std::string& nom, ParamInterface& param);
