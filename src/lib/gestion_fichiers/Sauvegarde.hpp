#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "../../include/ParamInterface.hpp"
#include "../../include/json-develop/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

void sauvegarderConfig(const std::string& cheminFichier,
    const std::string& nom, ParamInterface& param) 
{
    // Initialisation du JSON.
    json j;
    j["Nom du reseau"] = nom;

    j["IP source"] = {param.m_Source.a.to_ulong(), param.m_Source.b.to_ulong(), param.m_Source.c.to_ulong(), param.m_Source.d.to_ulong()};
    j["IP destination"] = {param.m_Destination.a.to_ulong(), param.m_Destination.b.to_ulong(), param.m_Destination.c.to_ulong(), param.m_Destination.d.to_ulong()};
    j["ssthresh"] = param.m_Ssthresh;
    j["Nombre de paquets"] = param.m_NbPaquet;
    j["Type de fichier"] = param.m_TypeFichier;

    // Ecriture.
    std::ofstream ecriture(cheminFichier);

    // setw pout l'affichage jolie de JSON.
    ecriture << std::setw(4) << j << std::endl;
}