#include <iostream>

#include "../../src/include/Commun.hpp"
#include "../../src/include/ParamInterface.hpp"
#include "../../src/lib/gestion_fichiers/Chargement.hpp"
#include "../../src/lib/gestion_fichiers/Sauvegarde.hpp"
#include "../../src/lib/reseau_graphe/machine/Routeur.hpp"
#include "../../src/lib/reseau_graphe/machine/Ordinateur.hpp"
#include "../../src/lib/reseau_graphe/machine/Commutateur.hpp"

void test1() {
    Machine m;
    std::cout << m << std::endl;

    Ordinateur pc, pc2;
    std::cout << pc << std::endl;
    std::cout << pc2 << std::endl;

    Commutateur s, s2;
    std::cout << s << std::endl;
    std::cout << s2 << std::endl;

    Routeur r, r2;
    std::cout << r << std::endl;
    std::cout << r2 << std::endl;
}

void test2() {
    std::unique_ptr<ReseauGraphe> reseau;

    ParamInterface p;
    p.m_Source = {192, 168, 1, 1};
    p.m_Destination = {192, 168, 1, 2};
    p.m_NbPaquet = 500;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;

    sauvegarderConfig("ecriture.json", "ReseauSimple", p);
    chargerConfig("ecriture.json", reseau, p);
    // std::cout << *reseau;

    Machine& clientM = reseau->getMachine(p.m_Source);
    Machine& serveurM = reseau->getMachine(p.m_Destination);

    Ordinateur client = dynamic_cast<Ordinateur&> (clientM);
    Ordinateur serveur = dynamic_cast<Ordinateur&> (serveurM);

    MAC macDest = {35, 11, 122, 213, 123, 169};
    client.remplirFileDonnees(p, macDest);

    std::cout << "clientM \n" << clientM;
    std::cout << "serveurM \n" << serveurM;
}

void test3() {
    Ordinateur pc, pc2;

    pc.setIp({192, 168, 1, 1});
    pc.setMac({205, 138, 107, 55, 153, 181});
    pc2.setIp({192, 168, 1, 2});
    pc2.setMac({35, 11, 122, 213, 123, 169});

    pc.setVoisin(pc2);
    pc2.setVoisin(pc);

    std::cout << pc << std::endl;
    std::cout << pc2 << std::endl;

    ParamInterface p;
    p.m_Destination = pc2.getIp();
    p.m_Source = pc.getIp();
    p.m_NbPaquet = 10;
    p.m_Ssthresh = 128;
    p.m_TypeFichier = FTP;

    // std::cout << "remplirFileDonnees\n";
    pc.remplirFileDonnees(p, pc2.getMac());
    // std::bitset<16> cwnd = 0;
    // std::cout << "slowStart\n";
    // pc.slowStart(cwnd, p.m_Ssthresh);
}

int main(void) {
    srand(time(NULL));
    // test1();
    // test2();
    test3();

    return 0;
}
