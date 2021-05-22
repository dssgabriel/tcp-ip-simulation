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
