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

/**
 * @brief Lit le fichier indique en parametre, et renvoie un ReseauGraphe.
 * 
 * @param nomFichier : Le fichier contenant les informations du reseau.
 * @return std::unique_ptr<ReseauGraphe> : Un pointeur sur le reseau initialise.
 */
std::unique_ptr<ReseauGraphe> chargerReseau(const std::string& nomFichier);

/**
 * @brief Lit le fichier de configuration en parametre pour connaitre le reseau
 *        souhaite par l'utilisateur.
 * 
 * @param cheminFichier : L'emplacement du fichier de configuration.
 * @param reseau : Le reseau a renvoyer avec les informations du ficheirs.
 * @param param : La configuration du l'utilisateur.
 */
void chargerConfig(const std::string& cheminFichier,
    std::unique_ptr<ReseauGraphe>& reseau, ParamInterface& param);
