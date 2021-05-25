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
    p.m_NbPaquet = 320;
    p.m_Ssthresh = 4;
    p.m_TypeFichier = FTP;

    //
    pc.remplirFileDonnees(p, pc2.getMac());

    //
    std::bitset<16> cwnd = 1;
    pc.lancerHorloge();
    pc.slowStart(cwnd, p.m_Ssthresh);
    pc.arreterHorloge();
    for (auto element : pc.getControleCongestion()){
        std::cout << "temps : " << element.m_Temps
            << ", valeur cwnd " << element.m_ValeurCwnd
            << " mode : " << element.m_Mode << std::endl;
    }
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
    ReseauGraphe r;
    r.ajouter(&pc);
    r.ajouter(&pc2);
    r.ajouter(&c);
    r.ajouter(&c2);

    r.ajouter(Liaison{0, 0, 1});
    r.ajouter(Liaison{0, 1, 2});
    r.ajouter(Liaison{0, 2, 3});

    //
    // int nbrPaquet = rand()%1000;
    int nbrPaquet = 15;

    //
    ParamInterface p;
    p.m_Destination = pc2.getIp();
    p.m_Source = pc.getIp();
    p.m_NbPaquet = nbrPaquet;
    // p.m_Ssthresh = rand()%1000;
    p.m_Ssthresh = 5;
    p.m_TypeFichier = FTP;
    std::cout << "p.m_NbPaquet : " << p.m_NbPaquet
        << ", p.m_Ssthresh : " << p.m_Ssthresh << std::endl;

    //
    pc.remplirFileDonnees(p, pc2.getMac());

    //
    // pc.envoyer(nbrPaquet, false);

    //
    std::bitset<16> cwnd = 1;
    pc.lancerHorloge();
    pc.slowStart(cwnd, p.m_Ssthresh);
    pc.arreterHorloge();
    std::cout << "\n\nAffichage tableau controle congestion : \n";
    for (auto element : pc.getControleCongestion()){
        std::cout << "temps : " << element.m_Temps
            << ", valeur cwnd " << element.m_ValeurCwnd
            << " mode : " << element.m_Mode << std::endl;
    }

    //
    std::cout << "\n\nAffichage tableau temps traitement : \n";
    auto tempsPaquet = r.getTempsPaquet();
    for (auto elt : tempsPaquet) {
        std::cout << "numpaquet : " << elt.first
            << ", temps : " << elt.second << " s\n";
    }
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
    sauvegarderConfig("ecriture.json", "ReseauPME", p);

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
    sauvegarderConfig("ecriture.json", "ReseauPME", p);

    //
    std::unique_ptr<ReseauGraphe> reseau;
    chargerConfig("ecriture.json", reseau, p);

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
    std::cout << "log #0 : Avant lancerOSPF\n";
    reseau->lancerOSPF();

    for (Machine* m: reseau->getMachines()) {
        Routeur* r = dynamic_cast<Routeur*>(m);
        if (r) {
            std::cout << *r << std::endl;
        }
    }

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

void test8() {
    int nbrPaquet = 1024;

    //
    ParamInterface p;
    p.m_Source = { 192, 168, 1, 11 };
    p.m_Destination = { 192, 168, 1, 40 };
    p.m_NbPaquet = nbrPaquet;
    p.m_Ssthresh = 256;
    p.m_TypeFichier = FTP;

    //
    sauvegarderConfig("ecriture.json", "ReseauEntreprise", p);

    std::unique_ptr<ReseauGraphe> reseau;
    chargerConfig("ecriture.json", reseau, p);

    //
    reseau->lancerOSPF();

    Machine* m = reseau->getMachine(p.m_Source);
    Ordinateur* pc = dynamic_cast<Ordinateur*> (m);

    //
    Machine* m2 = reseau->getMachine(p.m_Destination);
    Ordinateur* pc2 = dynamic_cast<Ordinateur*> (m2);

    //
    pc->remplirFileDonnees(p, pc2->getMac());

    //
    std::bitset<16> cwnd = 1;
    pc->lancerHorloge();
    pc->slowStart(cwnd, p.m_Ssthresh);
    pc->arreterHorloge();
    std::cout << "\n\nAffichage tableau controle congestion : \n";
    for (auto element : pc->getControleCongestion()){
        std::cout << "temps : " << element.m_Temps
            << ", valeur cwnd " << element.m_ValeurCwnd
            << " mode : " << element.m_Mode << std::endl;
    }

    //
    std::cout << "\n\nAffichage tableau temps traitement : \n";
    auto tempsPaquet = reseau->getTempsPaquet();
    for (auto elt : tempsPaquet) {
        std::cout << "numpaquet : " << elt.first
            << ", temps : " << elt.second << " s\n";
    }

    std::cout << "Nombre de paquets : " << p.m_NbPaquet
        << ", ssthresh : " << p.m_Ssthresh << std::endl;
}

void test9() {
    ParamInterface p;
    p.m_Source = { 192, 168, 1, 1 };
    p.m_Destination = { 192, 168, 1, 161 };
    p.m_NbPaquet = 15;
    p.m_Ssthresh = 5;
    p.m_TypeFichier = FTP;

    std::cout << "p.m_NbPaquet : " << p.m_NbPaquet
        << ", p.m_Ssthresh : " << p.m_Ssthresh << std::endl;

    sauvegarderConfig("ecriture.json", "ReseauPME", p);
    std::unique_ptr<ReseauGraphe> reseau;
    chargerConfig("ecriture.json", reseau, p);

    reseau->lancerOSPF();

    for (Machine* m: reseau->getMachines()) {
        Routeur* r = dynamic_cast<Routeur*>(m);
        if (r) {
            std::cout << *r << std::endl;
        }
    }
}

int main(void) {
    srand(time(NULL));
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    test8();
    // test9();

    return 0;
}
