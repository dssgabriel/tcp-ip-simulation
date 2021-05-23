#include <time.h>
#include <iostream>
#include <typeinfo>

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

    Machine* client = reseau->getMachine(p.m_Source);
    Machine* serveur = reseau->getMachine(p.m_Destination);

    MAC macDest = {35, 11, 122, 213, 123, 169};
    Ordinateur* pc = dynamic_cast<Ordinateur*>(client);
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
    p.m_NbPaquet = 32;
    p.m_Ssthresh = 4;
    p.m_TypeFichier = FTP;

    //
    pc.remplirFileDonnees(p, pc2.getMac());

    //
    std::bitset<16> cwnd = 1;
    pc.slowStart(cwnd, p.m_Ssthresh);
    // pc.envoyer(2);
    // pc.envoyer(3);
    // pc.envoyer(4, false);
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
    Routeur r, r2;
    r.setIp({192, 168, 1, 5});
    r.setMac({229, 73, 221, 65, 26, 32});
    r2.setIp({192, 168, 1, 6});
    r2.setMac({56, 51, 113, 150, 102, 83});

    //
    ParamInterface p;
    p.m_Source = pc.getIp();
    p.m_Destination = pc2.getIp();
    p.m_NbPaquet = nbrPaquet;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;
    sauvegarderConfig("ecriture.json", "ReseauMaison", p);

    //
    pc.setVoisin(c);
    c.setVoisin(pc);

    c.setVoisin(r);
    r.setVoisin(c);

    r.setVoisin(r2);
    r2.setVoisin(r);

    r2.setVoisin(c2);
    c2.setVoisin(r2);

    c2.setVoisin(pc2);
    pc2.setVoisin(c2);

    //
    c.setMemoire(&pc.getIp(), &pc.getMac());
    c.setMemoire(&pc2.getIp(), &r.getMac());
    c2.setMemoire(&pc.getIp(), &r2.getMac());
    c2.setMemoire(&pc2.getIp(), &pc2.getMac());

    //
    pc.remplirFileDonnees(p, pc2.getMac());

    //
    pc.envoyer(nbrPaquet, false);
}

void test6() {
    //
    int nbrPaquet = 1;

    //
    ParamInterface p;
    p.m_Source = {192, 168, 1, 1};
    p.m_Destination = {192, 168, 1, 194};
    p.m_NbPaquet = nbrPaquet;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;
    sauvegarderConfig("ecriture.json", "ReseauMaison", p);

    //
    std::unique_ptr<ReseauGraphe> reseau;
    chargerConfig("ecriture.json", reseau, p);

    //
    // Machine* m = reseau->getMachine(p.m_Source);
    // Ordinateur* pc = dynamic_cast<Ordinateur*> (m);

    //
    // Machine* m2 = reseau->getMachine(p.m_Destination);
    // Ordinateur* pc2 = dynamic_cast<Ordinateur*> (m2);

    // std::cout << *reseau;
    // Machine* m3 = reseau->getMachine({192, 168, 1, 65});
    // Routeur* r = dynamic_cast<Routeur*> (m3);
    // std::cout << *r << std::endl;

    //
    reseau->lancerOSPF();

    //
    // pc->remplirFileDonnees(p, pc2->getMac());
    // m->envoyer(nbrPaquet, false);
}

void test7() {
    //
    int nbrPaquet = 1;

    //
    ParamInterface p;
    p.m_Source = {192, 168, 1, 1};
    p.m_Destination = {192, 168, 1, 194};
    p.m_NbPaquet = nbrPaquet;
    p.m_Ssthresh = 136;
    p.m_TypeFichier = FTP;
    sauvegarderConfig("ecriture.json", "ReseauMaison", p);

    //
    std::unique_ptr<ReseauGraphe> reseau;
    chargerConfig("ecriture.json", reseau, p);

    //
    Machine* m = reseau->getMachine(p.m_Source);
    Ordinateur* pc = dynamic_cast<Ordinateur*>(m);

    //
    Machine* m2 = reseau->getMachine(p.m_Destination);
    Ordinateur* pc2 = dynamic_cast<Ordinateur*>(m2);

    //
    std::cout << "\n##########\n" << *reseau << "\n##########\n";

    //
    pc->remplirFileDonnees(p, pc2->getMac());

    //
    std::cout << "pc : " << *pc << std::endl;
    std::cout << "pc2 : " << *pc2 << std::endl;
    pc->envoyer(nbrPaquet, false);
}

int main(void) {
    srand(time(NULL));
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    test6();
    // test7();

    return 0;
}
