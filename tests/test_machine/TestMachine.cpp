#include <time.h>
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

    Machine* client = reseau->getMachinePtr(p.m_Source);
    Machine serveur = reseau->getMachine(p.m_Destination);

    MAC macDest = {35, 11, 122, 213, 123, 169};
    Ordinateur* pc = static_cast<Ordinateur*>(client);
    pc->remplirFileDonnees(p, macDest);

    std::cout << "client \n" << *client;
    std::cout << "serveur \n" << serveur;
}

void test3() {
    //
    Ordinateur pc, pc2;
    pc.setIp({192, 168, 1, 1});
    pc.setMac({205, 138, 107, 55, 153, 181});
    pc2.setIp({192, 168, 1, 2});
    pc2.setMac({35, 11, 122, 213, 123, 169});
    pc.setVoisin(pc2);
    pc2.setVoisin(pc);

    //
    ParamInterface p;
    p.m_Destination = pc2.getIp();
    p.m_Source = pc.getIp();
    p.m_NbPaquet = 4;
    p.m_Ssthresh = 8;
    p.m_TypeFichier = FTP;

    //
    pc.remplirFileDonnees(p, pc2.getMac());
    
    //
    // std::bitset<16> cwnd = 1;
    // pc.slowStart(cwnd, p.m_Ssthresh);
    // pc.envoyer(2);
    // pc.envoyer(3);
    pc.envoyer(4, false);
}

void test4() {
    //
    Ordinateur pc, pc2;
    pc.setIp({192, 168, 1, 1});
    pc.setMac({205, 138, 107, 55, 153, 181});
    pc2.setIp({192, 168, 1, 2});
    pc2.setMac({35, 11, 122, 213, 123, 169});

    //
    Commutateur c, c2;
    c.setIp({192, 168, 1, 3});
    c.setMac({213, 73, 221, 65, 26, 32});
    c2.setIp({192, 168, 1, 4});
    c2.setMac({40, 51, 229, 150, 102, 83});

    //
    pc.setVoisin(c);
    c.setVoisin(pc);
    c.setVoisin(c2);
    c2.setVoisin(c);
    c2.setVoisin(pc2);
    pc2.setVoisin(c2);

    //
    c.setMemoire(&pc.getIp(), &pc.getMac());
    c.setMemoire(&pc2.getIp(), &c2.getMac());
    c2.setMemoire(&pc.getIp(), &c.getMac());
    c2.setMemoire(&pc2.getIp(), &pc2.getMac());

    //
    ParamInterface p;
    p.m_Destination = pc2.getIp();
    p.m_Source = pc.getIp();
    int nbrPaquet = 2;
    p.m_NbPaquet = nbrPaquet;
    p.m_Ssthresh = 8;
    p.m_TypeFichier = FTP;

    //
    pc.remplirFileDonnees(p, pc2.getMac());

    //
    pc.envoyer(nbrPaquet, false);
}

void test5() {
    //
    int nbrPaquet = 1;

    //
    ParamInterface p;
    p.m_Source = {192, 168, 1, 1};
    p.m_Destination = {192, 168, 1, 129};
    p.m_NbPaquet = nbrPaquet;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;
    sauvegarderConfig("ecriture.json", "ReseauMaison", p);

    //
    std::unique_ptr<ReseauGraphe> reseau;
    chargerConfig("ecriture.json", reseau, p);

    //
    Machine* m = reseau->getMachinePtr(p.m_Source);
    Ordinateur* pc = static_cast<Ordinateur*>(m);
    std::cout << pc->getNom() << std::endl;
    
    //
    Machine* m2 = reseau->getMachinePtr(p.m_Destination);
    Ordinateur* pc2 = static_cast<Ordinateur*>(m2);
    std::cout << pc2->getNom() << std::endl;

    //
    // std::cout << "Reseau : " << *reseau << std::endl;

    //
    pc->remplirFileDonnees(p, pc2->getMac());

    //
    pc->envoyer(nbrPaquet, false);
}

int main(void) {
    srand(time(NULL));
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}
