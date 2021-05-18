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

    Machine& clientM = reseau->getMachine(p.m_Source);
    Machine& serveurM = reseau->getMachine(p.m_Destination);

    // Erreur : `std::bad_cast`
    Ordinateur client = dynamic_cast<Ordinateur&>(clientM);
    Ordinateur serveur = dynamic_cast<Ordinateur&>(serveurM);

    MAC macDest = {35, 11, 122, 213, 123, 169};
    client.remplirFileDonnees(p, macDest);

    std::cout << "clientM \n" << clientM;
    std::cout << "serveurM \n" << serveurM;
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
<<<<<<< HEAD:test/testsMachine/testMachine.cpp
    
=======

>>>>>>> 1451a1037ed666f3030dc74040c179b794b06f4e:tests/test_machine/TestMachine.cpp
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

int main(void) {
    srand(time(NULL));
<<<<<<< HEAD:test/testsMachine/testMachine.cpp
    // test1();
    // test2();
    // test3();
    // test4();
=======
    //test1();
    //test2();
    //test3();
    test4();
>>>>>>> 1451a1037ed666f3030dc74040c179b794b06f4e:tests/test_machine/TestMachine.cpp

    return 0;
}
