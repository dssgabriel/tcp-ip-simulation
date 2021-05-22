#include "Sauvegarde.hpp"

void sauvegarderConfig(const std::string& cheminFichier,
    const std::string& nom, ParamInterface& param) 
{
    // Ouverture du fichier.
    std::ofstream ecriture(cheminFichier);
    if(ecriture.fail()) {
        std::cout << "ERREUR : Dans le fichiers 'Sauvegarde.cpp'. ";
        std::cout << "Dans la fonction 'sauvegarderConfig'. ";
        std::cout << "Fichier JSON introuvable.\n";
        exit(EXIT_FAILURE);
    }

    // Initialisation de l'objet JSON.
    json j;

    // Remplissage du JSON avec la configuration.
    j["Nom du reseau"] = nom;
    j["IP source"] = {
        param.m_Source.a.to_ulong(),
        param.m_Source.b.to_ulong(),
        param.m_Source.c.to_ulong(),
        param.m_Source.d.to_ulong()
    };
    j["IP destination"] = {
        param.m_Destination.a.to_ulong(),
        param.m_Destination.b.to_ulong(),
        param.m_Destination.c.to_ulong(),
        param.m_Destination.d.to_ulong()
    };
    j["ssthresh"] = param.m_Ssthresh;
    j["Nombre de paquets"] = param.m_NbPaquet;
    j["Type de fichier"] = param.m_TypeFichier;

    // Ecriture dans le fichier.
    // setw -> pour un affichage jolie de JSON.
    ecriture << std::setw(4) << j << std::endl;
}
