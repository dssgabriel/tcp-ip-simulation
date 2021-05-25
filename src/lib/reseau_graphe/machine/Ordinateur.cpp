/**
 * @file Ordinateur.cpp
 * @author Mickael Le Denmat
 * @brief Vous trouverez ici toutes les fonctions implementees
 *          pour la classe Ordinateur.
 * @date 2021-05-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Ordinateur.hpp"

uint8_t Ordinateur::m_NbOrdinateur = 0;

/**
 * @brief Constructeur de la classe Ordinateur.
 *
 */
Ordinateur::Ordinateur() : Machine() {
    m_NbOrdinateur++;
    m_IdOrdinateur = m_NbOrdinateur;

    m_Nom = "Ordinateur" + std::to_string(m_IdOrdinateur);

    m_ControleCongestion.clear();
    m_TempsTraitementPaquet.clear();
}

/**
 * @brief Destructeur de la classe Ordinateur.
 *
 */
Ordinateur::~Ordinateur() {
    m_NbOrdinateur--;
}

/**
 * @brief Accesseur du nombre d'ordinateur.
 *
 * @return const uint8_t& le nombre d'ordinateur.
 */
const uint8_t& Ordinateur::getNbrOrdinateur() const {
    return m_NbOrdinateur;
}

/**
 * @brief Acceseur de l'identifiant de l'ordinateur.
 *
 * @return const uint8_t& l'identifiant de l'ordinateur.
 */
const uint8_t& Ordinateur::getIdOrdinateur() const {
    return m_IdOrdinateur;
}

/**
 * @brief Accesseur du tableau de controle de congestion.
 *
 * @return const std::vector<ElementControleCongestion>& le tableau de controle
 *          de congestion.
 */
const std::vector<ElementControleCongestion>& Ordinateur::getControleCongestion() const {
    return m_ControleCongestion;
}

/**
 * @brief Accesseur d'un element dans le tableau de controle de congestion.
 *
 * @param position dans le tableau.
 * @return const ElementControleCongestion& le tableau de controle de congestion.
 */
const ElementControleCongestion& Ordinateur::getControleCongestion(const int& position) const {
    if (position < 0 || position > (int)m_ControleCongestion.size()) {
        std::cout << "ERREUR : Dans le fichier 'Ordinateur.cpp'. "
            << "Dans la fonction 'getControleCongestion'. "
            << "Position en dehors du tableau.\n";
        exit(EXIT_FAILURE);
    }

    return m_ControleCongestion[position];
}

/**
 * @brief 
 * 
 */
void Ordinateur::freeControleCongestion() {
    m_ControleCongestion.clear();
}


/**
 * @brief Genere un message aleatoire pour les trames.
 *
 * @return std::bitset<16> le message.
 */
std::bitset<16> genererMessage() {
    uint16_t tmp = rand() % 2^16;
    return std::bitset<16> (tmp);
}

/**
 * @brief Verifie s'il existe un tripleAck, dans notre cas un ack est different du
 *          numero de sequence de la prochaine trame a envoyer.
 *
 * @param donnees la file d'attente de donnees.
 * @return true s'il existe un tripleACK.
 * @return false sinon.
 */
bool tripleACK(std::deque<std::stack<std::bitset<16>>> &donnees) {
	for (int i = 0; i < int(donnees.size()); i++) {

		// Initialisation des couches.
		Physique couchePhy;
		Internet coucheInt;
		Transport coucheTrans;

		// Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

		uint32_t ack2Convert = coucheTrans.getAck2().to_ulong();

		// Encapsulation.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donnees[i] = couchePhy.encapsuler(paquet);

        // Si la trame desencapusle est un ack.
		if (ack2Convert != 0) {

            // On regarde les derniers ack mis dans la file.
			for (int j = i - 1; i <= 0; --j) {

				// Initialisation des couches.
				Physique couchePhy2;
				Internet coucheInt2;
				Transport coucheTrans2;

				// Desencapsulation.
				std::stack<std::bitset<16>> paquet = couchePhy2.desencapsuler(donnees[j]);
				std::stack<std::bitset<16>> segment = coucheInt2.desencapsuler(paquet);
				std::bitset<16> donnee = coucheTrans2.desencapsuler(segment);

				uint32_t seqConvert = coucheTrans2.getSeq().to_ulong();

				// Encapsulation.
				segment = coucheTrans.encapsuler(donnee);
				paquet = coucheInt.encapsuler(segment);
				donnees[i] = couchePhy.encapsuler(paquet);

                // l'ack est t'il correct ?
				if (seqConvert == ack2Convert) {
					return true;
				}
			}
		}

	}
	return false;
}

/**
 * @brief Calcul le nombre de trame qu'il reste a envoyer.
 *
 * @param donnees la file d'attente.
 * @return int le nombre de trame a envoyer.
 */
int calculerNombreEnvoye(std::deque<std::stack<std::bitset<16>>> &donnees) {

    // Initialisation des variables, des couches.
    int compteur = 0;
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

    // On parcours les ack.
    for (int i = 0; i < int(donnees.size()); ++i) {

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        if (coucheTrans.getAck2().to_ulong() == 0) {
            compteur++;
        }

        // Encapsulation.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donnees[i] = couchePhy.encapsuler(paquet);
    }

    return compteur;
}

/**
 * @brief FONCTIONNALITE NON PRISE EN CHARGE
 *          Indique si le paquet est en fin de vie ou non.
 *
 * @param paquet pour verifier le 'flag TTL'
 * @return true sinon la vie du paquet est a 0.
 * @return false sinon.
 */
bool timeout(std::stack<std::bitset<16>> paquet) {

    // Desencapsulation.
    Internet coucheInt;
    std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);

    // Si le TTL est a 0, alors le paquet est en timeout.
    if (coucheInt.getTTL().to_ulong() == 0) {
        // Encapsulation.
        paquet = coucheInt.encapsuler(segment);

        return true;
    } else {
        // Encapsulation.
        paquet = coucheInt.encapsuler(segment);
    }

    return false;
}

/**
 * @brief FONCTIONNALITE NON PRISE EN CHARGE
 *          Indique si le ack est duplique dans la file d'attente.
 *
 * @param donnees la file d'attente.
 * @param ack a verifier.
 * @param pos la position du ack duplique.
 * @return true si le ack est duplique et on renseigne la pos.
 * @return false sinon.
 */
bool estDuplique(
    std::deque<std::stack<std::bitset<16>>> donnees,
    const std::bitset<32>& ack,
    const int& pos)
{
    if (ack.to_ulong() == 0) {
        return false;
    }

    // On regarde un ack.
    for (int i = 0; i < int(donnees.size()) - 2; ++i) {
        if (i == pos) {
            continue;
        }

        // Initialisation des couches.
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // Encapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Desencapulation.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donnees[i] = couchePhy.encapsuler(paquet);

        // Verifie si l'ack existe deja.
        if (coucheTrans.getAck2() == ack) {
            return true;
        }
    }

    return false;
}

/**
 * @brief FONCTIONNALITE NON PRISE EN CHARGE
 *          Renvoie la donnee correspondante au numero de la trame.
 *
 * @param donnees la file d'attente.
 * @param seq le numero de la trame.
 * @return std::stack<std::bitset<16>> la donnee trouvee, exit sinon.
 */
std::stack<std::bitset<16>> trouverDonnee(
        std::deque<std::stack<std::bitset<16>>> &donnees,
        const std::bitset<32>& seq)
{
    // Initialisation des couches.
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

    // On parcourt la file d'attente.
    for (int i = 0; i < int(donnees.size()); ++i) {

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // on verifie que ce soit la bonne trame.
        if (coucheTrans.getSeq() == seq) {

            // Encapsulation.
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            donnees[i] = couchePhy.encapsuler(paquet);

            return donnees[i];
        }
    }

    // Si on ne trouve pas la donnee.
    std::cout << "ERREUR : Dans le fichier 'Ordinateur.cpp'. "
        << "Dans la fonction 'trouverDonnee'. "
        << "Aucune donnée\n";
    exit(EXIT_FAILURE);
}

/**
 * @brief Rempli la file de donnee avec la configuration donnee par l'utilisateur.
 *
 * @param config donnee par l'utilisateur.
 * @param destination l'adresse MAC de destination.
 */
void Ordinateur::remplirFileDonnees(
    const ParamInterface& config, const MAC& destination)
{
    // Preparation des donnees
    for (size_t i = 0; i < config.m_NbPaquet; ++i) {

        // Initialisation
        Transport coucheTrans;
        Internet coucheInt;
        Physique couchePhy;

        // Encapsulation couche Transport
        coucheTrans.setPortSrc(coucheTrans.portAlea());
        coucheTrans.setPortDest(config.m_TypeFichier);
        coucheTrans.setCwnd(std::bitset<16>(0));
        coucheTrans.setSyn(std::bitset<16>(1));
        coucheTrans.setAck1(std::bitset<16>(0));
        coucheTrans.setSeq(std::bitset<32>(i+1));
        coucheTrans.setAck2(std::bitset<32>(0));
        coucheTrans.calculerChecksum(); // <=> setChecksum()
        std::stack<std::bitset<16>> segment;
        segment = coucheTrans.encapsuler(genererMessage());

        // Encapsulation couche Internet
        coucheInt.setIpSrc(config.m_Source);
        coucheInt.setIpDest(config.m_Destination);
        coucheInt.setTTL(std::bitset<8> (100));
        coucheInt.setProtocoleId();
        coucheInt.calculerChecksum();
        std::stack<std::bitset<16>> paquet;
        paquet = coucheInt.encapsuler(segment);

        // Encapsulation couche Physique
        couchePhy.setMacSrc(m_Mac);
        couchePhy.setMacDest(destination);
        std::stack<std::bitset<16>> trame;
        trame = couchePhy.encapsuler(paquet);

        //
        setDonnee(trame);
    }
}

/**
 * @brief FONCTIONNALITE NON PRISE EN CHARGE
 *          Etablie la connexion entre la machine emetrice et receptrice.
 *
 */
void Ordinateur::synchroniser() {
    // TODO : A faire
}

/**
 * @brief FONCTIONNALITE NON PRISE EN CHARGE
 *          Coupe la session entre la machine emetrice et receptrice.
 *
 */
void Ordinateur::finDeSession() {
    // TODO : A faire
}

/**
 * @brief Envoie une trame.
 *
 * @param cwnd le nombre de trame a envoyer.
 * @param estAck indique si la trame est un accuse de reception.
 */
void Ordinateur::envoyer(const uint32_t cwnd, const bool estAck) {
    if (DEBUG) {
        std::cout << m_Nom << " : Debut envoie\n";
    }

	if (estAck) { // Partie accuse de reception.
        if (DEBUG) {
            std::cout << m_Nom << " : Retour\n";
        }
		return;
	}
    if (DEBUG) {
        std::cout << m_Nom << " : Aller\n";
    }

    // Partie envoie donnee.

    // Trouver la machine voisine.
    // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
    Machine* voisine = m_Voisins.front();

    // Envoie des cwnd trames.
    for (int i = 0; i < int(cwnd); ++i) {

        // Verifie que toutes les trames sont envoyees.
        if (calculerNombreEnvoye(m_FileDonnees) == 0) {
            if (DEBUG) {
                std::cout << VERT << m_Nom
                    << " : Plus de trame a envoyer, fin de la session\n" << RESET;
            }
            return;
        }

        // Vide la file de donnees.
        std::stack<std::bitset<16>> donneeRecu = suppDonnee();

        // Creation des couches pour desencapsulation.
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donneeRecu);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Encapsulation
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donneeRecu = couchePhy.encapsuler(paquet);

        // Initialisation du cwnd.
        coucheTrans.setCwnd(cwnd);

        // Traitement de la donnee.
        traitement(donneeRecu, voisine->getMac());

        // La machine suivante recois le paquet
        voisine->setDonnee(donneeRecu);
    }

    //
    voisine->recevoir(cwnd, estAck);
    if (DEBUG) {
        std::cout << m_Nom << " : Fin envoie\n";
    }
}

/**
 * @brief Recois la trame.
 *
 * @param cwnd Le nombre de trame recu.
 * @param estAck La trame recu est un accuse de reception ou non.
 */
void Ordinateur::recevoir([[maybe_unused]] const uint32_t cwnd,
    [[maybe_unused]] const bool estAck)
{
    if (DEBUG) {
        std::cout << m_Nom << " : Debut recevoir\n";
    }
    if (estAck) { // Partie accuse de reception.
        return;
    }

    // Partie envoie donnee.

    // Creation des couches pour desencapsulation.
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

    // Si on recoit une trame.
    if (int(m_FileDonnees.size()) == 1) {

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[0]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // Initialisation de l'ack.
        std::bitset<32> ack = std::bitset<32>(coucheTrans.getSeq().to_ulong() + 1);
        coucheTrans.setAck2(ack);

        // Encapsulation.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        m_FileDonnees[0] = couchePhy.encapsuler(paquet);

        //
        if (DEBUG) {
            std::cout << VERT << m_Nom << " : Paquet ok\n" << RESET
                << m_Nom << " : Fin recevoir\n";
        }

        // Trouver la machine voisine.
        // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
        Machine* voisine = m_Voisins.front();

        // Envoie de l'acusse de reception.
        voisine->setDonnee(m_FileDonnees[0]);
		suppDonnee();
        voisine->envoyer(1, true);
        return;
    }

    // Si on recoit plusieurs trames.
    int i;
    for (i = 1; i < int(m_FileDonnees.size()); ++i) {

        // Creation des couches pour desencapsulation.
        Physique couchePhy2;
        Internet coucheInt2;
        Transport coucheTrans2;

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet2 = couchePhy2.desencapsuler(m_FileDonnees[i]);
        std::stack<std::bitset<16>> segment2 = coucheInt2.desencapsuler(paquet2);
        std::bitset<16> donnee2 = coucheTrans2.desencapsuler(segment2);

        // Desencapsulation.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[i-1]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        //
        if (DEBUG) {
            std::cout << "coucheTrans.getSeq().to_ulong() : " << coucheTrans.getSeq().to_ulong()
                << ", coucheTrans2.getSeq().to_ulong() : " << coucheTrans2.getSeq().to_ulong();
        }

        // Verification perte de trame.
        if (int(coucheTrans.getSeq().to_ulong()) + 1 != int(coucheTrans2.getSeq().to_ulong())) {
            //
            if (DEBUG) {
                std::cout << ROUGE << " ECHEC\n" << RESET;
                std::cout << ROUGE << m_Nom << " : Manque un paquet : " << coucheTrans2.getSeq().to_ulong() << RESET << std::endl;
            }

            // Initialisation ack.
            std::bitset<32> ack = std::bitset<32>(coucheTrans.getSeq().to_ulong() + 1);
            coucheTrans.setAck2(ack);

            // Encapsulation.
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            m_FileDonnees[i-1] = couchePhy.encapsuler(paquet);

            //
            if (DEBUG) {
                std::cout << m_Nom << " : Fin recevoir\n";
            }

            // Trouver la machine voisine.
            // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
            Machine* voisine = m_Voisins.front();

            // Envoie accuse reception indiquant perte de trame.
            voisine->setDonnee(m_FileDonnees[i-1]);
            m_FileDonnees.clear();
            voisine->envoyer(1, true);
            return;
        }
        if (DEBUG) {
            std::cout << VERT << " OK\n" << RESET;
        }

        // Partie sans perte de trame.

        // Initialisation ack.
        std::bitset<32> ack = std::bitset<32>(coucheTrans2.getSeq().to_ulong() + 1);
        coucheTrans2.setAck2(ack);

        // Encapsulation.
        segment2 = coucheTrans2.encapsuler(donnee2);
        paquet2 = coucheInt2.encapsuler(segment2);
        m_FileDonnees[i] = couchePhy2.encapsuler(paquet2);
    }

    //
    if (DEBUG) {
        std::cout << VERT << m_Nom << " : Tous les paquets sont ok" << RESET << std::endl;
        std::cout << m_Nom << " : Fin recevoir\n";
    }

    // Trouver la machine voisine.
    // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
    Machine* voisine = m_Voisins.front();

    // Envoie ack.
    voisine->setDonnee(m_FileDonnees[i-1]);
	m_FileDonnees.clear();
    voisine->envoyer(1, true);
}

/**
 * @brief Controle de congestion : Algorithme de Slow Start.
 *
 * @param cwnd le nombre de trame a envoyer.
 * @param ssthresh1 le nombre maximum de trame a envoyer en meme temps.
 */
void Ordinateur::slowStart(std::bitset<16>& cwnd, uint16_t& ssthresh1) {
    std::cout
        << "\t###############\n"
        << "\tDebut slowStart\n"
        << "\t###############\n";

    //
    uint64_t cwndConvert = cwnd.to_ulong();

    // Creation element controle de congestion pour l'interface.
    ElementControleCongestion ecc;
    ecc.m_Temps = m_Chrono.getTempsSec().count();
    ecc.m_ValeurCwnd = cwndConvert;
    ecc.m_Mode = SlowStart;
    m_ControleCongestion.push_back(ecc);

    //
    if (cwndConvert < ssthresh1) {

        //
        for (int i = 0; i < calculerNombreEnvoye(m_FileDonnees); ++i) {

            // Fin de slow start, on depasse le nombre maximum de trame.
            if (cwndConvert >= ssthresh1) {
                std::cout
                    << "\t#############################\n"
                    << "\tif (cwndConvert >= ssthresh1)\n"
                    << "\t#############################\n";
                cwndConvert /= 2;
                cwnd = std::bitset<16>(cwndConvert);
                congestionAvoidance(cwnd, ssthresh1);
                return;
            } else {
                envoyer(cwndConvert, false);
                cwndConvert *= 2;
                cwnd = std::bitset<16> (cwndConvert);
            }

            //
            if (cwndConvert < ssthresh1) {
                ElementControleCongestion ecc;
                ecc.m_Temps = m_Chrono.getTempsSec().count();
                ecc.m_ValeurCwnd = cwndConvert;
                ecc.m_Mode = SlowStart;
                m_ControleCongestion.push_back(ecc);
            }
        }

        // Si il reste des trames non envoyees.
        if (calculerNombreEnvoye(m_FileDonnees) != 0) {
                envoyer(calculerNombreEnvoye(m_FileDonnees), false);
        }
    } else {
        std::cout
            << "\t####\n"
            << "\telse\n"
            << "\t####\n";
        congestionAvoidance(cwnd, ssthresh1);
        return;
    }

    std::cout
        << "\t#############\n"
        << "\tFin slowStart\n"
        << "\t#############\n";
}

/**
 * @brief Controle de congestion : Algorithme de Congestion Avoidance.
 *
 * @param cwnd le nombre de trame a envoyer.
 * @param ssthresh le nombre maximum de trame a envoyer en meme temps.
 */
void Ordinateur::congestionAvoidance(std::bitset<16>& cwnd, uint16_t& ssthresh) {
    std::cout
        << "\t#########################\n"
        << "\tDebut congestionAvoidance\n"
        << "\t#########################\n";

    Physique couchePhy;
    uint64_t cwndConvert = cwnd.to_ulong();

    // FONCTIONNALITE NON PRISE EN CHARGE
    // if (tripleACK(m_FileDonnees)) {
    //     ssthresh = cwndConvert / 2;
    //     cwndConvert /= 2;
    //     fastRetransmit(std::bitset<32> (ackTripleConvert - 1), cwnd, ssthresh);
    //     std::cout
    //         << "\t#######################\n"
    //         << "\tFin congestionAvoidance\n"
    //         << "\t#######################\n";
	// 	return;
    // }

    //
    for (int i = 0; i < calculerNombreEnvoye(m_FileDonnees); ++i) {
	    cwndConvert += 1;

        //
        ElementControleCongestion ecc;
        ecc.m_Temps = m_Chrono.getTempsSec().count();
        ecc.m_ValeurCwnd = cwndConvert;
        ecc.m_Mode = CongestionAvoidance;
        m_ControleCongestion.push_back(ecc);

        //
        cwnd = std::bitset<16> (cwndConvert);

        //
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[i]);
        m_FileDonnees[i] = couchePhy.encapsuler(paquet);

        // FONCTIONNALITE NON PRISE EN COMPTE.
        // if (timeout(paquet)) {
        //     ssthresh = cwndConvert / 2;
        //     cwndConvert = 1;
        //     cwnd = std::bitset<16> (cwndConvert);
        //     slowStart(cwnd, ssthresh);
        //     std::cout
        //         << "\t#######################\n"
        //         << "\tFin congestionAvoidance\n"
        //         << "\t#######################\n";
        //     return;
        // } else {
		// 	envoyer(cwndConvert, false);
        // }
    	envoyer(cwndConvert, false);
    }

    // Si il reste des trames non envoyees.
	if (calculerNombreEnvoye(m_FileDonnees) != 0) {
		envoyer(calculerNombreEnvoye(m_FileDonnees), false);
	}

    //
    std::cout
        << "\t#######################\n"
        << "\tFin congestionAvoidance\n"
        << "\t#######################\n";
}

/**
 * @brief FONCTIONNALITE NON PRISE EN COMPTE.
 *          Controle de congestion : Algorithme Fast Retransmit.
 *
 * @param seq le numero de la trame.
 * @param cwnd le nombre de trame a envoyer.
 * @param ssthresh le nombre maximum de trame a envoyer en meme temps.
 */
void Ordinateur::fastRetransmit([[maybe_unused]] const std::bitset<32>& seq,[[maybe_unused]]  std::bitset<16>& cwnd, [[maybe_unused]] uint16_t& ssthresh) {
    // std::cout
    //     << "\t####################\n"
    //     << "\tDebut fastRetransmit\n"
    //     << "\t####################\n";
    // std::stack<std::bitset<16>> s = trouverDonnee(m_FileDonnees, seq);
    // setDonnee(s);
    // std::cout
    //     << "\t##################\n"
    //     << "\tFin fastRetransmit\n"
    //     << "\t##################\n";
    // fastRecovery(cwnd, ssthresh);
}

/**
 * @brief FONCTIONNALITE NON PRISE EN COMPTE.
 *          Controle de congestion : Algorithme Fast Recovery.
 *
 * @param cwnd le nombre de trame a envoyer.
 * @param ssthresh le nombre maximum de trame a envoyer en meme temps.
 */
void Ordinateur::fastRecovery([[maybe_unused]] std::bitset<16>& cwnd,[[maybe_unused]]  uint16_t& ssthresh) {
    // std::cout
    //     << "\t##################\n"
    //     << "\tDebut fastRecovery\n"
    //     << "\t##################\n";
    // uint64_t cwndConvert = cwnd.to_ulong();
    // ssthresh = cwndConvert / 2;
    // cwndConvert = ssthresh + 3;
    // cwnd = std::bitset<16>(cwndConvert);

    // //
    // for (int i = 0; i < calculerNombreEnvoye(m_FileDonnees); ++i) {
    //     // Initialisation des couches.
    //     Physique couchePhy;
    //     Internet coucheInt;
    //     Transport coucheTrans;

    //     // On desencapsule.
    //     std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[i]);
    //     std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
    //     std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

    //     //
    //     if (coucheTrans.getAck2() == 0) {
    //         continue;
    //     }
    //     if (estDuplique(m_FileDonnees, coucheTrans.getAck2(), i)) {
    //         cwndConvert += 1;
    //         cwnd = std::bitset<16>(cwndConvert);
    //     } else {
    //         cwndConvert = ssthresh;
    //         cwnd = std::bitset<16>(cwndConvert);

    //         // On re encapusle.
    //         segment = coucheTrans.encapsuler(donnee);
    //         paquet = coucheInt.encapsuler(segment);
    //         m_FileDonnees[i] = couchePhy.encapsuler(paquet);
    //         std::cout << "\tFin fastRecovery\n";
    //         congestionAvoidance(cwnd, ssthresh);
    //         return;
    //     }
    // }
    // std::cout
    //     << "\t################\n"
    //     << "\tFin fastRecovery\n"
    //     << "\t################\n";
}
