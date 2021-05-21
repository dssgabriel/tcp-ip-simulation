#include "Chargement.hpp"

std::unique_ptr<ReseauGraphe> chargerReseau(const std::string& nomFichier) {

    // Initialisation du reseau.
    ReseauGraphe* reseau = new ReseauGraphe();
    if (!reseau) {
        std::cout << "ERREUR : Dans la fonction 'chargerReseau' : pointeur nul.\n";
        return std::unique_ptr<ReseauGraphe>(nullptr);
    }

    // Lecture du fichier.
    std::ifstream lecture(nomFichier);
    if (lecture.fail()) {
        std::cout << "ERREUR : Dans la fonction 'chargerReseau' : Fichier JSON introuvable.\n";
        exit(EXIT_FAILURE);
    }

    // Convertion du fichier en JSON.
    json j;
    lecture >> j;

    // Remplissage du reseau.
    reseau->setNom(j["Nom du reseau"]);

    // Initialisation variables.
    Machine* m = nullptr;
    IPv4 ip;
    MAC mac;

    // Remplissage de la liste des machines.
    auto listeMachineJ = j["Liste machines"];
    for (auto machineJ : listeMachineJ) {
        // Initialisation du type de machine.
        if (machineJ["type"] == "Ordinateur") {
            m = new Ordinateur();
        } else if (machineJ["type"] == "Routeur") {
            m = new Routeur();
        } else if (machineJ["type"] == "Commutateur") {
            m = new Commutateur();
        } else {
            std::cout << "ERREUR : Dans la fonction 'chargerReseau' : Type de machine inconnu\n.";
            exit(EXIT_FAILURE);
        }

        // Initialisation des attributs la machine.
        // Adresse IP.
        ip.a = std::bitset<8>(machineJ["ip"][0]);
        ip.b = std::bitset<8>(machineJ["ip"][1]);
        ip.c = std::bitset<8>(machineJ["ip"][2]);
        ip.d = std::bitset<8>(machineJ["ip"][3]);
        m->setIp(ip);

        // Adresse MAC.
        mac.a = std::bitset<8>(machineJ["mac"][0]);
        mac.b = std::bitset<8>(machineJ["mac"][1]);
        mac.c = std::bitset<8>(machineJ["mac"][2]);
        mac.d = std::bitset<8>(machineJ["mac"][3]);
        mac.e = std::bitset<8>(machineJ["mac"][4]);
        mac.f = std::bitset<8>(machineJ["mac"][5]);
        m->setMac(mac);

        // Masque de reseau.
        ip.a = std::bitset<8>(machineJ["masque"][0]);
        ip.b = std::bitset<8>(machineJ["masque"][1]);
        ip.c = std::bitset<8>(machineJ["masque"][2]);
        ip.d = std::bitset<8>(machineJ["masque"][3]);
        m->setMasque(ip);

        // Masque de sous reseau.
        // Possede jusqu'a 4 masque de sous reseau.
        auto obj = machineJ["sous reseaux"][0];
        if (!obj["ip"].is_null()) {
            ip.a = std::bitset<8>(obj["ip"][0]);
            ip.b = std::bitset<8>(obj["ip"][1]);
            ip.c = std::bitset<8>(obj["ip"][2]);
            ip.d = std::bitset<8>(obj["ip"][3]);

            // Ajout du masque de sous reseau.
            m->setSousReseau(ip);
        }
        if (!obj["ip2"].is_null()) {
            ip.a = std::bitset<8>(obj["ip2"][0]);
            ip.b = std::bitset<8>(obj["ip2"][1]);
            ip.c = std::bitset<8>(obj["ip2"][2]);
            ip.d = std::bitset<8>(obj["ip2"][3]);

            m->setSousReseau(ip);
        }
        if (!obj["ip3"].is_null()) {
            ip.a = std::bitset<8>(obj["ip3"][0]);
            ip.b = std::bitset<8>(obj["ip3"][1]);
            ip.c = std::bitset<8>(obj["ip3"][2]);
            ip.d = std::bitset<8>(obj["ip3"][3]);

            m->setSousReseau(ip);
        }
        if (!obj["ip4"].is_null()) {
            ip.a = std::bitset<8>(obj["ip4"][0]);
            ip.b = std::bitset<8>(obj["ip4"][1]);
            ip.c = std::bitset<8>(obj["ip4"][2]);
            ip.d = std::bitset<8>(obj["ip4"][3]);

            m->setSousReseau(ip);
        }

        // Ajout de la machine creee dans le reseau.
        reseau->ajouter(*m);
    }

    // Remplissage de la liste des liaisons.
    auto listeLiaisonsJ = j["Liste liaisons"];
    for (auto liaisonJ : listeLiaisonsJ) {
        Liaison l;
        l.m_NumMachine1 = liaisonJ["Depart"];
        l.m_NumMachine2 = liaisonJ["Arrivee"];
        l.m_Debit = liaisonJ["Debit"];

        // Ajout de la liaison dans le reseau.
        reseau->ajouter(l);

        // Configuration des voisins.
        Machine* a = reseau->getMachine(l.m_NumMachine1);
        Machine* b = reseau->getMachine(l.m_NumMachine2);
        a->setVoisin(*b);
        b->setVoisin(*a);
    }

    // Remplissage cache memoire des commutateurs.
    auto listeMemJ = j["table memoire"];
    Commutateur* c = dynamic_cast<Commutateur*>(m);
    for (auto memJ : listeMemJ) {
        ip.a = std::bitset<8>(memJ["ip"][0]);
        ip.b = std::bitset<8>(memJ["ip"][1]);
        ip.c = std::bitset<8>(memJ["ip"][2]);
        ip.d = std::bitset<8>(memJ["ip"][3]);

        mac.a = std::bitset<8>(memJ["mac"][0]);
        mac.b = std::bitset<8>(memJ["mac"][1]);
        mac.c = std::bitset<8>(memJ["mac"][2]);
        mac.d = std::bitset<8>(memJ["mac"][3]);
        mac.e = std::bitset<8>(memJ["mac"][4]);
        mac.f = std::bitset<8>(memJ["mac"][5]);

        c->setMemoire(&ip, &mac);
    }

    // Convertion.
    return std::unique_ptr<ReseauGraphe>(reseau);
}

/**
 * @brief Lit le fichier de configuration en parametre pour connaitre le reseau
 *        souhaite par l'utilisateur.
 *
 * @param cheminFichier : L'emplacement du fichier de configuration.
 * @param reseau : Le reseau a renvoyer avec les informations du ficheirs.
 * @param param : La configuration du l'utilisateur.
 */
void chargerConfig(const std::string& cheminFichier,
    std::unique_ptr<ReseauGraphe>& reseau, ParamInterface& param)
{
    // Lecture du fichier de configuration.
    std::ifstream lecture(cheminFichier);
    if (lecture.fail()) {
        std::cout << "ERREUR : Dans la fonction 'chargerConfig' : ";
        std::cout << "Fichier JSON introuvable.\n";
        exit(EXIT_FAILURE);
    }

    // Convertion du fichier de configuration en JSON.
    json j;
    lecture >> j;

    // Chargement du reseau correspondant.
    std::string choixReseau = j["Nom du reseau"];
    if (choixReseau == "ReseauSimple") {
        reseau = chargerReseau("../../src/include/configReseau/ReseauSimple.json");
    } else if (choixReseau == "ReseauMaison") {
        reseau = chargerReseau("../../src/include/configReseau/ReseauMaison.json");
    } else if (choixReseau == "ReseauPme") {
        reseau = chargerReseau("../../src/include/configReseau/ReseauPme.json");
    } else if (choixReseau == "ReseauEntreprise") {
        reseau = chargerReseau("../../src/include/configReseau/ReseauEntreprise.json");
    } else {
        std::cout << "ERREUR : Dans la fonction 'chargerConfig' : ";
        std::cout << "Reseau choisi inconnu.\n";
        exit(EXIT_FAILURE);
    }

    // Chargement des parametres de configuration.
    IPv4 ip;
    ip.a = std::bitset<8>(j["IP destination"][0]);
    ip.b = std::bitset<8>(j["IP destination"][1]);
    ip.c = std::bitset<8>(j["IP destination"][2]);
    ip.d = std::bitset<8>(j["IP destination"][3]);
    param.m_Destination = ip;

    ip.a = std::bitset<8>(j["IP source"][0]);
    ip.b = std::bitset<8>(j["IP source"][1]);
    ip.c = std::bitset<8>(j["IP source"][2]);
    ip.d = std::bitset<8>(j["IP source"][3]);
    param.m_Source = ip;

    param.m_NbPaquet = j["Nombre de paquets"];
    param.m_Ssthresh = j["ssthresh"];
    param.m_TypeFichier = j["Type de fichier"];
}
