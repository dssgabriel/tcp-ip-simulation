/**
 * @file Machine.cpp
 * @author Mickael LE DENMAT
 * @brief Vous trouverez ici toutes les fonctions implementees
 *          pour la classe Machine.
 * @date 2021-05-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Machine.hpp"

/**
 * @brief Variables prédéfinies pour initialiser des adresses IP.
 *
 */
IPv4 ipZero = {
    .a = std::bitset<8>(0),
    .b = std::bitset<8>(0),
    .c = std::bitset<8>(0),
    .d = std::bitset<8>(0)
};

IPv4 ipMax = {
    .a = std::bitset<8>(255),
    .b = std::bitset<8>(255),
    .c = std::bitset<8>(255),
    .d = std::bitset<8>(255)
};

/**
 * @brief Variables prédéfinies pour initialiser des adresses MAC.
 *
 */
MAC macZero = {
    .a = std::bitset<8>(0),
    .b = std::bitset<8>(0),
    .c = std::bitset<8>(0),
    .d = std::bitset<8>(0),
    .e = std::bitset<8>(0),
    .f = std::bitset<8>(0)
};

MAC macMax = {
    .a = std::bitset<8>(255),
    .b = std::bitset<8>(255),
    .c = std::bitset<8>(255),
    .d = std::bitset<8>(255),
    .e = std::bitset<8>(255),
    .f = std::bitset<8>(255)
};

uint16_t Machine::m_NbMachine = 0;

/**
 * @brief Constructeur de la classe Machine
 *
 */
Machine::Machine() {
    m_NbMachine++;
    m_IdMachine = m_NbMachine;

    m_Nom = "Machine" + std::to_string(m_IdMachine);

    m_Ip = ipZero;
    m_Mac = macZero;
    m_Masque = ipZero;
    m_SousReseau.clear();

    m_Voisins.clear();

    while(!m_FileDonnees.empty()) {
        m_FileDonnees.pop_back();
    }
}

/**
 * @brief Destructeur de la classe Machine.
 *
 */
Machine::~Machine() {
    m_NbMachine--;
}

/**
 * @brief Accesseur du nombre de machine.
 *
 * @return const uint16_t& le nombre de machine.
 */
const uint16_t& Machine::getNbMachine() const {
    return m_NbMachine;
}

/**
 * @brief Accesseur de l'identifiant de la machine.
 *
 * @return const uint16_t& l'identifiant de la machine.
 */
const uint16_t& Machine::getIdMachine() const {
    return m_IdMachine;
}

/**
 * @brief Mutateur du nom de la machine.
 *
 * @param nom de la machine.
 */
void Machine::setNom(const std::string& nom) {
    m_Nom = nom;
}

/**
 * @brief Accesseur du nom de la machine.
 *
 * @return const std::string& le nom de la machine.
 */
const std::string& Machine::getNom() const {
    return m_Nom;
}

/**
 * @brief Mutateur de l'adresse IP de la machine.
 *
 * @param ip de la machine.
 */
void Machine::setIp(const IPv4& ip) {
    m_Ip = ip;
}

/**
 * @brief Accesseur de l'adresse IP de la machine.
 *
 * @return const IPv4& l'adresse IP de la machine.
 */
const IPv4& Machine::getIp() const {
    return m_Ip;
}

/**
 * @brief Mutateur du masque du reseau.
 *
 * @param masque du reseau.
 */
void Machine::setMasque(const IPv4& masque) {
    m_Masque = masque;
}

/**
 * @brief Accesseur du masque du reseau.
 *
 * @return const IPv4& le masque du reseau.
 */
const IPv4& Machine::getMasque() const {
    return m_Masque;
}

/**
 * @brief Mutateur de l'adresse MAC de la machine.
 *
 * @param mac de la machine.
 */
void Machine::setMac(const MAC& mac) {
    m_Mac = mac;
}

/**
 * @brief Accesseur de l'adresse MAC de la machine.
 *
 * @return const MAC& l'adresse MAC de la machine.
 */
const MAC& Machine::getMac() const {
    return m_Mac;
}

/**
 * @brief Ajout d'un masque de sous reseau.
 *
 * @param sousReseau de la machine.
 */
void Machine::setSousReseau(const IPv4& sousReseau) {
    m_SousReseau.emplace_back(sousReseau);
}

/**
 * @brief Accesseur du tableau de sous reseaux.
 *
 * @return const std::vector<IPv4>& le tableau de sous reseau.
 */
const std::vector<IPv4>& Machine::getSousReseaux() const {
    return m_SousReseau;
}

/**
 * @brief Ajout d'un voisin a la machine.
 *
 * @param voisin de la machine.
 */
void Machine::setVoisin(Machine& voisin) {
    m_Voisins.emplace_back(&voisin);
}

/**
 * @brief Accesseur du voisin possedant l'adresse MAC renseigne.
 *
 * @param adresseVoisin adresse MAC pour trouver le voisin.
 * @return Machine* le voisin.
 */
Machine* Machine::getVoisin(MAC adresseVoisin) const {
    for (Machine *m : m_Voisins) {
        if (m->getMac() == adresseVoisin) {
            return m;
        }
    }

    std::cout << "ERREUR : Dans le fichier 'Machine.cpp'. "
        << "Dans la fonction 'getVoisin'. "
        << "Aucune voisin trouve.\n";
    exit(EXIT_FAILURE);
}

/**
 * @brief Accesseur du tableau du voisin.
 *
 * @return std::vector<Machine*> le tableau de voisin.
 */
std::vector<Machine*> Machine::getVoisins() const {
    return m_Voisins;
}

/**
 * @brief Ajout d'une trame dans la file d'attente.
 *
 * @param trame a mettre dans la file d'attente.
 */
void Machine::setDonnee(const std::stack<std::bitset<16>>& trame) {
    m_FileDonnees.emplace_back(trame);
}

/**
 * @brief Accesseur de la liste d'attente.
 *
 * @return std::queue<std::stack<std::bitset<16>>>& la liste d'attente.
 */
std::deque<std::stack<std::bitset<16>>>& Machine::getDonnees() {
    return m_FileDonnees;
}

/**
 * @brief Supprime la premiere trame dans la file d'attente.
 *
 * @return std::stack<std::bitset<16>> la trame supprime.
 */
std::stack<std::bitset<16>> Machine::suppDonnee() {
    if (!m_FileDonnees.empty()) {
        std::stack<std::bitset<16>> premiereTrame = m_FileDonnees.front();
        m_FileDonnees.pop_front();
        return premiereTrame;
    } else {
        std::cout << "ERREUR : Dans le fichier 'Machine.cpp'. "
            << "Dans la fonction 'suppDonnee'. "
            << "Impossible de supprimer un élément, file vide.\n";
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Accesseur d'un element dans le tableau de temps de traitement.
 *
 * @param numPaquet le numero du paquet.
 * @return double le temps de traitement du paquet.
 */
const double& Machine::getTempsTraitementPaquet(const uint32_t& numPaquet) const {
    auto trouve = m_TempsTraitementPaquet.find(numPaquet);
    if (trouve != m_TempsTraitementPaquet.end()) {
        return trouve->second;
    }

    std::cout << "ERREUR : Dans le fichier 'Ordinateur.cpp'. "
        << "Dans la fonction 'getTempsTraitementPaquet'. "
        << "Aucun paquet ne correspond au numero demande.\n";
    exit(EXIT_FAILURE);
}

/**
 * @brief Accesseur du tableau de temps de traitement des paquets.
 *
 * @return const std::map<uint16_t, double> le tableau de temps de traitement.
 */
const std::map<uint32_t, double>& Machine::getTempsTraitementPaquets() const {
    return m_TempsTraitementPaquet;
}

/**
 * @brief Traite une trame lors de l'enoie de cette derniere dans le reseau.
 *          Met l'adresse MAC de destination en adresse source.
 *          Remplace l'adresse MAC de destination par la nouvelle destination.
 *
 * @param trame a traiter.
 * @param nouvelleDest de la machine voisine.
 */
void Machine::traitement(std::stack<std::bitset<16>> &trame, MAC nouvelleDest) {
    //
    if (DEBUG) {
        std::cout << m_Nom << BLUE << " : Debut traitement\n" << RESET;
    }

    // Debut temps traitement.
    Horloge o;
    o.lancer();

    // Recuperation du paquet et desencapsulation.
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

    //
    std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(trame);
    std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
    std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

    // FONCTIONNALITE NON PRISE EN CHARGE.
    // coucheInt.setTTL(std::bitset<8>(coucheInt.getTTL().to_ulong() - 1));

    // Recuperation adresse MAC destination.
    MAC ancienneDest = couchePhy.getMacDest();

    // Changement adresse MAC.
    couchePhy.setMacSrc(ancienneDest);
    couchePhy.setMacDest(nouvelleDest);

    // Encapsulation.
    segment = coucheTrans.encapsuler(donnee);
    paquet = coucheInt.encapsuler(segment);
    trame = couchePhy.encapsuler(paquet);

    // Ajout temps traitement dans la 'map'.
    o.arreter();
    m_TempsTraitementPaquet.emplace(coucheTrans.getSeq().to_ulong(), o.getTempsSec().count());

    //
    if (DEBUG) {
        std::cout << m_Nom << BLUE << " : fin traitement\n" << RESET;
    }
}

/**
 * @brief Lance le chrono de l'horloge.
 *
 */
void Machine::lancerHorloge() {
    m_Chrono.lancer();
}

/**
 * @brief Arrete le chrono de l'horloge.
 *
 */
void Machine::arreterHorloge() {
    m_Chrono.arreter();
    m_Chrono.remettreAZero();
}

/**
 * @brief Redefinition de l'operateur d'affichage.
 *
 * @param flux a modifier avec les informations de la machine.
 * @param m a afficher.
 * @return std::ostream& l'affichage des informations de la machine.
 */
std::ostream& operator<<(std::ostream& flux, const Machine& m) {
    flux << "Numero : " << m.getIdMachine() << "/" << m.getNbMachine() << std::endl;
    flux << "Nom : " << m.getNom() << std::endl;
    flux << "Ip : " << m.getIp() << std::endl;
    flux << "Masque : " << m.getMasque() << std::endl;
    flux << "Mac : " << m.getMac() << std::endl;

    flux << "Liste des sous réseaux : \n";
    std::vector<IPv4> cpySousReseau = m.getSousReseaux();
    for (IPv4 sousReseau : cpySousReseau) {
        flux << "\t > " << sousReseau << std::endl;
    }

    flux << "Liste des voisins : \n";
    std::vector<Machine*> cpyVoisins = m.getVoisins();
    for (Machine* voisine : cpyVoisins) {
        flux << "\t > " << voisine->getIp() << std::endl;
    }

    return flux;
}
