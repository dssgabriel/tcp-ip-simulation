#include <iostream>

#include "../src/include/ParamInterface.hpp"
#include "../src/lib/gestion_fichiers/Chargement.hpp"
#include "../src/lib/gestion_fichiers/Sauvegarde.hpp"

int main(void) {
    ParamInterface p;
    p.m_Source = {192, 240, 20, 1};
    p.m_Destination = {168, 4, 125, 6};
    p.m_NbPaquet = 500;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;
    
    sauvegarderConfig("test/testEcritureJson.json", "configTest", p);

    return 0;
}
