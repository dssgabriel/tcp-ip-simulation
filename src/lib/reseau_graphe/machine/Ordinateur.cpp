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

uint8_t Ordinateur::m_NbrOrdinateur = 0;

/**
 * @brief Constructeur de la classe Ordinateur.
 * 
 */
Ordinateur::Ordinateur() : Machine() {
    m_NbrOrdinateur++;
    m_IdOrdinateur = m_NbrOrdinateur;

    m_Nom = "Ordinateur" + std::to_string(m_IdOrdinateur);

    m_ControleCongestion.clear();
    m_TempsTraitementPaquet.clear();
}

/**
 * @brief Destructeur de la classe Ordinateur.
 * 
 */
Ordinateur::~Ordinateur() {}

/**
 * @brief Accesseur du nombre d'ordinateur.
 * 
 * @return const uint8_t& le nombre d'ordinateur.
 */
const uint8_t& Ordinateur::getNbrOrdinateur() const {
    return m_NbrOrdinateur;
}

/**
 * @brief Acceseur de l'identifiant de l'ordinateur.
 * 
 * @return const uint8_t& l'identifiant.
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
 * @brief Accesseur du tableau de temps de traitement des paquets.
 * 
 * @return const std::map<uint16_t, double> le tableau de temps de traitement.
 */
const std::map<uint16_t, double> Ordinateur::getTempsTraitementPaquet() const {
    return m_TempsTraitementPaquet;
}

/**
 * @brief Accesseur d'un element dans le tableau de controle de congestion.
 * 
 * @param position dans le tableau.
 * @return const ElementControleCongestion& 
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
 * @brief Accesseur d'un element dans le tableau de temps de traitement.
 * 
 * @param cle le numero du paquet.
 * @return double le temps de traitement du paquet.
 */
double Ordinateur::getTempsTraitementPaquet(const uint16_t& cle) const {
    auto trouve = m_TempsTraitementPaquet.find(cle);
    if (trouve != m_TempsTraitementPaquet.end()) {
        return trouve->second;
    }

    std::cout << "ERREUR : Dans le fichier 'Ordinateur.cpp'. "
        << "Dans la fonction 'getTempsTraitementPaquet'. "
        << "Aucun paquet ne correspond au numero demande.\n";
    exit(EXIT_FAILURE);
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
 * @brief Convertir une file en double file.
 * 
 * @param queue a convertir.
 * @return std::deque<std::stack<std::bitset<16>>> la double file.
 */
std::deque<std::stack<std::bitset<16>>> convertirQueueDeque(
    std::queue<std::stack<std::bitset<16>>> queue)
{
    std::deque<std::stack<std::bitset<16>>> dequeu;
    while(!queue.empty()) {
        dequeu.emplace_back(queue.front());
        queue.pop();
    }

    return dequeu;   
}

bool tripleACK(std::deque<std::stack<std::bitset<16>>> &donnees)
{
	for (int i = 0; i < int(donnees.size()); i++) {
		// Initialisation des couches.
		Physique couchePhy;
		Internet coucheInt;
		Transport coucheTrans;

		// On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

		uint32_t ack2Convert = coucheTrans.getAck2().to_ulong();

		// On re encapsule.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donnees[i] = couchePhy.encapsuler(paquet);
		if (ack2Convert != 0) {
			for (int j = i - 1; i <= 0; --j) {
				// Initialisation des couches.
				Physique couchePhy2;
				Internet coucheInt2;
				Transport coucheTrans2;

				// On desencapsule.
				std::stack<std::bitset<16>> paquet = couchePhy2.desencapsuler(donnees[j]);
				std::stack<std::bitset<16>> segment = coucheInt2.desencapsuler(paquet);
				std::bitset<16> donnee = coucheTrans2.desencapsuler(segment);

				uint32_t seqConvert = coucheTrans2.getSeq().to_ulong();

				// On re encapsule.
				segment = coucheTrans.encapsuler(donnee);
				paquet = coucheInt.encapsuler(segment);
				donnees[i] = couchePhy.encapsuler(paquet);

				if (seqConvert == ack2Convert) {
					return true;
				}
			}
		}
		
	}
	return false;
}

int calculerNombreEnvoye(std::deque<std::stack<std::bitset<16>>> &donnees) {
    int compteur = 0;
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

    // On parcours les ack.
    for (int i = 0; i < int(donnees.size()); ++i) {
		
        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        if (coucheTrans.getAck2().to_ulong() == 0) {
            compteur++;
        }

        // On re encapsule.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donnees[i] = couchePhy.encapsuler(paquet);
    }

    return compteur;
}

bool timeout(std::stack<std::bitset<16>> paquet) {
    // On desencapsule.
    Internet coucheInt;
    std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);

    // Si le TTL est a 0, alors le paquet est en timeout.
    if (coucheInt.getTTL().to_ulong() == 0) {
        // On re encapsule.
        paquet = coucheInt.encapsuler(segment);

        return true;
    } else {
        // On re encapsule.
        paquet = coucheInt.encapsuler(segment);
    }

    return false;
}

bool estDuplique(
    std::deque<std::stack<std::bitset<16>>> &donnees,
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

        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // On re encapusle.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        donnees[i] = couchePhy.encapsuler(paquet);  

        if (coucheTrans.getAck2() == ack) {
            std::cout << "paquet dupliqué\n";
            return true;
        }
    }

    return false;
}

std::stack<std::bitset<16>> trouverDonnee(
        std::deque<std::stack<std::bitset<16>>> &donnees,
        const std::bitset<32>& seq)
{
    //
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

    //
    for (int i = 0; i < int(donnees.size()); ++i) {
        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(donnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        // on verifie que ce soit la bonne trame.
        if (coucheTrans.getSeq() == seq) {

            // Je re encapsule.
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            donnees[i] = couchePhy.encapsuler(paquet);

            return donnees[i];
        }
    }

    std::cout << "ERREUR : Dans le fichier 'Ordinateur.cpp'. ";
    std::cout << "Dans la fonction 'trouverDonnee'. ";
    std::cout << "Aucune donnée\n";
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
        // std::cout << coucheTrans;

        // Encapsulation couche Internet
        coucheInt.setIpSrc(config.m_Source);
        coucheInt.setIpDest(config.m_Destination);
        coucheInt.setTTL(std::bitset<8> (100));
        coucheInt.setProtocoleId();
        coucheInt.calculerChecksum();
        std::stack<std::bitset<16>> paquet;
        paquet = coucheInt.encapsuler(segment);
        // std::cout << coucheInt;

        // Encapsulation couche Physique
        couchePhy.setMacSrc(m_Mac);
        couchePhy.setMacDest(destination);
        std::stack<std::bitset<16>> trame;
        trame = couchePhy.encapsuler(paquet);
        // std::cout << couchePhy << std::endl;

        //
        setDonnee(trame);
        // afficher(trame);
    }
}

void Ordinateur::synchroniser() {
    // TODO : A faire
}

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
	std::cout << m_Nom << " : Debut envoie\n";

	if (estAck) {
		std::cout << m_Nom << " : Retour\n";
		return;
	}
	std::cout << m_Nom << " : Aller\n";
	
    // Trouver la machine voisine.
    // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
    Machine* voisine = m_Voisins.front();

    // Envoie des cwnd trames.
    for (int i = 0; i < int(cwnd); ++i) {
        //

        if (calculerNombreEnvoye(m_FileDonnees) == 0) {
            std::cout << m_Nom << " : Plus de paquets a envoyer, fin de la session\n";
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
        
        //
        coucheTrans.setCwnd(cwnd);
        
        // Traitement de la donnee.
        traitement(donneeRecu, voisine->getMac());

        // La machine suivante recois le paquet
        voisine->setDonnee(donneeRecu);
    }

    //
    voisine->recevoir(cwnd, estAck);
    std::cout << m_Nom << " : Fin envoie\n";
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
    std::cout << m_Nom << " : Debut recevoir\n";
    if (estAck) {
        return;
    }

    // Creation des couches pour desencapsulation.
    Physique couchePhy;
    Internet coucheInt;
    Transport coucheTrans;

	std::cout << m_FileDonnees.size() << std::endl;
    if (int(m_FileDonnees.size()) == 1) {
        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[0]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        //
        std::bitset<32> ack = std::bitset<32>(coucheTrans.getSeq().to_ulong() + 1);
        coucheTrans.setAck2(ack);

        // Encapsulation.
        segment = coucheTrans.encapsuler(donnee);
        paquet = coucheInt.encapsuler(segment);
        m_FileDonnees[0] = couchePhy.encapsuler(paquet);

        //
        std::cout << m_Nom << " : Paquet ok" << std::endl;
        std::cout << m_Nom << " : Fin recevoir\n";

        // Trouver la machine voisine.
        // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
        Machine* voisine = m_Voisins.front();

        voisine->setDonnee(m_FileDonnees[0]);
		suppDonnee();
        voisine->envoyer(1, true);
        return;
    }

    //
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
        if (int(coucheTrans.getSeq().to_ulong()) + 1 != int(coucheTrans2.getSeq().to_ulong())) {
            //
            std::cout << m_Nom << " : Manque un paquet : " << coucheTrans2.getSeq().to_ulong() << std::endl;
            std::bitset<32> ack = std::bitset<32>(coucheTrans.getSeq().to_ulong() + 1);
            coucheTrans.setAck2(ack);

            // Encapsulation.
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            m_FileDonnees[i-1] = couchePhy.encapsuler(paquet);

            //
            std::cout << m_Nom << " : Fin recevoir\n";

            // Trouver la machine voisine.
            // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
            Machine* voisine = m_Voisins.front();

            voisine->setDonnee(m_FileDonnees[i-1]);
			m_FileDonnees.clear();
			voisine->envoyer(1, true);
            return;
        }

        std::bitset<32> ack = std::bitset<32>(coucheTrans2.getSeq().to_ulong() + 1);
        coucheTrans2.setAck2(ack);

        // Encapsulation.
        segment2 = coucheTrans2.encapsuler(donnee2);
        paquet2 = coucheInt2.encapsuler(segment2);
        m_FileDonnees[i] = couchePhy2.encapsuler(paquet2);
    }

    //
    std::cout << m_Nom << " : Tous les paquets sont ok" << std::endl;
    std::cout << m_Nom << " : Fin recevoir\n";

    // Trouver la machine voisine.
    // Une seule machine voisine pour un ordinateur (routeur ou commutateur).
    Machine* voisine = m_Voisins.front();

    voisine->setDonnee(m_FileDonnees[i-1]);
	m_FileDonnees.clear();
    voisine->envoyer(1, true);
}

void Ordinateur::slowStart(std::bitset<16>& cwnd, uint16_t& ssthresh1) {
    std::cout << "Debut slowStart\n";

    //
    uint64_t cwndConvert = cwnd.to_ulong();
    std::cout << "log #0 : " << m_Chrono.getTempsSec().count() << std::endl;
    m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec().count(), cwndConvert, SlowStart});
    if (cwndConvert < ssthresh1) {
		    std::cout << calculerNombreEnvoye(m_FileDonnees) << std::endl;
    
            for (int i = 0; i < calculerNombreEnvoye(m_FileDonnees); ++i) {
                if (cwndConvert >= ssthresh1) {
				            std::cout << "On entre dans congestionAvoidance1" << std::endl;
				            cwndConvert /= 2;
                    // m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec2().count(), cwndConvert, SlowStart});
                  
				            cwnd = std::bitset<16>(cwndConvert);
				            congestionAvoidance(cwnd, ssthresh1);
				            return;
			          } else {
				            std::cout << "On envoie\n";
            				envoyer(cwndConvert, false);
				            cwndConvert *= 2;

                    if (cwndConvert < ssthresh1) {
                        m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec().count(), cwndConvert, SlowStart});
                    }
				            cwnd = std::bitset<16> (cwndConvert);
			          }
            }
		
            if (calculerNombreEnvoye(m_FileDonnees) != 0) {
			          envoyer(calculerNombreEnvoye(m_FileDonnees), false);
		        }
    } else {
            std::cout << "On entre dans congestionAvoidance2\n";
            congestionAvoidance(cwnd, ssthresh1);
            return;
        }
        std::cout << "Fin slowStart\n";
    }

void Ordinateur::congestionAvoidance(std::bitset<16>& cwnd, uint16_t& ssthresh) {
    std::cout << "On entre dans congestionAvoidance\n";

    Physique couchePhy;
    uint64_t cwndConvert = cwnd.to_ulong();
    // m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec2().count(), cwndConvert, CongestionAvoidance});

    //
    if (tripleACK(m_FileDonnees)) {
        ssthresh = cwndConvert / 2;
        cwndConvert /= 2;
        // m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec2().count(), cwndConvert, CongestionAvoidance});

        //fastRetransmit(std::bitset<32> (ackTripleConvert - 1), cwnd, ssthresh);
        fastRecovery(cwnd, ssthresh);
		return;
    }
    
    //
    for (int i = 0; i < calculerNombreEnvoye(m_FileDonnees); ++i) {
		std::cout << calculerNombreEnvoye(m_FileDonnees) << std::endl;
	    cwndConvert += 1;
        m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec().count(), cwndConvert, CongestionAvoidance});

        cwnd = std::bitset<16> (cwndConvert);

        //
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[i]);
        m_FileDonnees[i] = couchePhy.encapsuler(paquet);
        if (timeout(paquet)) {
            ssthresh = cwndConvert / 2;
            cwndConvert = 1;
            // m_ControleCongestion.push_back(ElementControleCongestion{m_Chrono.getTempsSec2().count(), cwndConvert, CongestionAvoidance});
            cwnd = std::bitset<16> (cwndConvert);
            slowStart(cwnd, ssthresh);
        } else {

			//std::cout << "cwnd : " << cwndConvert << " ssthresh : " << ssthresh << std::endl;
            envoyer(cwndConvert, false);
        }
    }
	if (calculerNombreEnvoye(m_FileDonnees) != 0) {
		//std::cout << "cwnd : " << cwndConvert << " ssthresh : " << ssthresh << std::endl;
		envoyer(calculerNombreEnvoye(m_FileDonnees), false);
	}
	
	
	std::cout << calculerNombreEnvoye(m_FileDonnees) << std::endl;
}

void Ordinateur::fastRetransmit([[maybe_unused]] const std::bitset<32>& seq,[[maybe_unused]]  std::bitset<16>& cwnd, [[maybe_unused]] uint16_t& ssthresh) {
    /*std::cout << "On entre dans fastRetransmit\n";
    std::stack<std::bitset<16>> s = trouverDonnee(m_FileDonnees, seq);
    setDonnee(s);
    fastRecovery(cwnd, ssthresh);*/
}

void Ordinateur::fastRecovery([[maybe_unused]] std::bitset<16>& cwnd,[[maybe_unused]]  uint16_t& ssthresh) {
    //
    /*std::cout << "On entre dans fastRecovery\n";
    uint64_t cwndConvert = cwnd.to_ulong();
    ssthresh = cwndConvert / 2;
    cwndConvert = ssthresh + 3;
    cwnd = std::bitset<16>(cwndConvert);

    //
    for (int i = 0; i < calculerNombreEnvoye(m_FileDonnees); ++i) {
        // Initialisation des couches.
        Physique couchePhy;
        Internet coucheInt;
        Transport coucheTrans;

        // On desencapsule.
        std::stack<std::bitset<16>> paquet = couchePhy.desencapsuler(m_FileDonnees[i]);
        std::stack<std::bitset<16>> segment = coucheInt.desencapsuler(paquet);
        std::bitset<16> donnee = coucheTrans.desencapsuler(segment);

        //
        if (coucheTrans.getAck2() == 0) {
            continue;
        }
        if (estDuplique(m_FileDonnees, coucheTrans.getAck2(), i)) {
            cwndConvert += 1;
            cwnd = std::bitset<16>(cwndConvert);
        } else {
            cwndConvert = ssthresh;
            cwnd = std::bitset<16>(cwndConvert);
            
            // On re encapusle.
            segment = coucheTrans.encapsuler(donnee);
            paquet = coucheInt.encapsuler(segment);
            m_FileDonnees[i] = couchePhy.encapsuler(paquet); 

            congestionAvoidance(cwnd, ssthresh);
            return;
        }
    }*/
}