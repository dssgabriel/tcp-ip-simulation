#include <iostream>

#include "../../src/include/ParamInterface.hpp"
#include "../../src/lib/gestion_fichiers/Chargement.hpp"
#include "../../src/lib/gestion_fichiers/Sauvegarde.hpp"

void test1() {
    ParamInterface p;
    p.m_Source = {192, 240, 20, 1};
    p.m_Destination = {168, 4, 125, 6};
    p.m_NbPaquet = 500;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;
    
    sauvegarderConfig("TestJson/ecriture.json", "configTest", p);
}

void test2() {
    std::unique_ptr<ReseauGraphe> reseau = chargerReseau("../../src/include/configReseau/ReseauSimple.json");
}

int main(void) {
    test1();
    test2();

    return 0;
}
