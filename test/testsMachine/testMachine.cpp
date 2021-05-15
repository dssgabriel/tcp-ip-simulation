#include <iostream>
#include <time.h>

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
<<<<<<< HEAD
    //
    Ordinateur pc, pc2;
=======
<<<<<<< HEAD
    //
    Ordinateur pc, pc2;
=======
    Ordinateur pc, pc2;

>>>>>>> 9360b6e580d686e911ecb0b06a885c23798a30c7
>>>>>>> c9cc145b1baa458df604abdce7f55be89e7d6b60
    pc.setIp({192, 168, 1, 1});
    pc.setMac({205, 138, 107, 55, 153, 181});
    pc2.setIp({192, 168, 1, 2});
    pc2.setMac({35, 11, 122, 213, 123, 169});
<<<<<<< HEAD
=======
<<<<<<< HEAD
    pc.setVoisin(pc2);
    pc2.setVoisin(pc);

    // std::cout << pc << std::endl;
    // std::cout << pc2 << std::endl;

    //
    ParamInterface p;
    p.m_Destination = pc2.getIp();
    p.m_Source = pc.getIp();
    p.m_NbPaquet = 2;
    p.m_Ssthresh = 8;
    p.m_TypeFichier = FTP;

    //
    pc.remplirFileDonnees(p, pc2.getMac());
    // afficher(pc.getDonnees());
    
    //
    std::bitset<16> cwnd = 1;
    // pc.slowStart(cwnd, p.m_Ssthresh);
    pc.envoyer(2);
=======

>>>>>>> c9cc145b1baa458df604abdce7f55be89e7d6b60
    pc.setVoisin(pc2);
    pc2.setVoisin(pc);

    // std::cout << pc << std::endl;
    // std::cout << pc2 << std::endl;

    //
    ParamInterface p;
    p.m_Destination = pc2.getIp();
    p.m_Source = pc.getIp();
    // p.m_NbPaquet = 2;
    // p.m_NbPaquet = 3;
    p.m_NbPaquet = 4;
    p.m_Ssthresh = 8;
    p.m_TypeFichier = FTP;

    //
    pc.remplirFileDonnees(p, pc2.getMac());
    // afficher(pc.getDonnees());
    
    //
    // std::bitset<16> cwnd = 1;
    // pc.slowStart(cwnd, p.m_Ssthresh);
<<<<<<< HEAD
    // pc.envoyer(2);
    // pc.envoyer(3);
    pc.envoyer(4);
=======
>>>>>>> 9360b6e580d686e911ecb0b06a885c23798a30c7
>>>>>>> c9cc145b1baa458df604abdce7f55be89e7d6b60
}

int main(void) {
    srand(time(NULL));
    // test1();
    // test2();
    test3();

    return 0;
}
