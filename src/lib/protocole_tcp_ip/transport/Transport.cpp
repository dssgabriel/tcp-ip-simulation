/**
 * transport.cpp : Vous trouverez ici toutes les fonctions implemente pour la classe Transport.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#include "Transport.hpp"

/**
  * @brief Constructeur de la classe Transport.
 * 
  * Le constructeur est vide car nous utilisons les setters pour initialiser les differents paramètres.
  * 
  * @return NULL. 
  **/
Transport::Transport() {
	
}

/**
  * @brief Destucteur de la classe Transport.
  * 
  * Le destructeur est vide car tout est géré par le 'garbage collector'.
  * 
  * @return NULL.
  **/
Transport::~Transport() {

}

/**
  * @brief Setter de l'attribut de classe m_PortSrc.
  * 
  * @param src : La valeur du port source souhaité.
  * @return void.
  **/
void Transport::setPortSrc(const uint16_t& src) {
    m_PortSrc = src;
}

/**
  * @brief Getter de l'attribut de classe m_PortSrc.
  * 
  * @return La valeur de l'attribut m_PortSrc. 
  **/
uint16_t &Transport::getPortSrc() {
    return m_PortSrc;
}

/**
  * @brief Setter de l'attribut m_PortDest de la classe Transport
  * 
  * @param num : La structure contenant le type de fichier que l'on va envoyer.
  * @return void.
  **/
void Transport::setPortDest(TypeFichier num) {
    switch(num){
        case 0:
            m_PortDest = 20;
            break;
        case 1:
            m_PortDest = 80;
            break;
        case 2:
            m_PortDest = 465;
            break;
        case 3:
            m_PortDest = 69;
            break;
        default:
            m_PortDest = 666;
    }
}

/**
  * @brief Getter de l'attribut de classe m_PortDest.
  *  
  * @return La valeur de m_PortDest.
  **/
uint16_t &Transport::getPortDest() {
    return m_PortDest;
}

/**
  * @brief Setter de l'attribut de classe m_Cwnd.
  * 
  * @param cwnd La valeur du cwnd souhaitée.
  * @return void.
  **/
void Transport::setCwnd(const std::bitset<16>& cwnd) {
    m_Cwnd = cwnd;
}

/**
  * @brief Getter de l'attribut de classe m_Cwnd.
  * 
  * @return La valeur du cwnd.
  **/
std::bitset<16> &Transport::getCwnd() {
    return m_Cwnd;
}

/**
  * @brief Setter de m_Checksum, attribut de la classe Transport.
  * 
  * @param checksum La valeur du checksum souhaitée.
  * @return void.
  **/
void Transport::setChecksum(const std::bitset<16>& checksum) {
    m_Checksum = checksum;
}

/**
  * @brief Getter de m_Checksum, attribut de la classe Transport.
  *
  * @return La valeur du checksum.
  **/
std::bitset<16>& Transport::getChecksum() {
    return m_Checksum;
}

/**
  * @brief Setter de m_Syn, attribut de classe de Transport. 
  * 
  * @param syn La valeur du syn souhaitée.
  * @return void.
  **/
void Transport::setSyn(const std::bitset<16>& syn) {
    m_Syn = syn;
}

/**
  * @brief Getter de l'attribut de classe m_Syn.
  * 
  * @return La valeur de m_Syn. 
  **/
std::bitset<16> &Transport::getSyn() {
    return m_Syn;
}

/**
  * @brief Setter de l'attribut m_Ack1.
  * 
  * @param ack1 Valeur de l'ack qu'on souhaite données
  * @return void.
  **/
void Transport::setAck1(const std::bitset<16>& ack1) {
    m_Ack1 = ack1;
}

/**
  * @brief Getter de l'attribut m_Ack1.
  * 
  * @return La valeur de m_Ack1.
  **/
std::bitset<16> &Transport::getAck1() {
    return m_Ack1;
}

/**
  * @brief Setter de l'attribut de classe m_Seq.
  * 
  * @param numSeq La valeur de m_Seq souhaitée.
  * @return void.
  **/
void Transport::setSeq(const std::bitset<32>& numSeq) {
    m_Seq = numSeq;
}

/**
  * @brief Getter de l'attribut de classe m_Seq.
  * 
  * @return La valeur de l'attribut m_Seq. 
  **/
std::bitset<32>& Transport::getSeq() {
    return m_Seq;
}

/**
  * @brief Setter de l'attribut m_Ack2.
  * 
  * @param ack2 La valeur de m_Ack2 souhaitée.
  * @return void.
  **/
void Transport::setAck2(const std::bitset<32>& ack2) {
    m_Ack2 = ack2;
}

/**
  * @brief Getter de l'attribut m_Ack2.
  * 
  * @return La valeur de m_Ack2. 
  **/
std::bitset<32> &Transport::getAck2() {
    return m_Ack2;
}

/**
  * @brief Permet de produire un nombre aléatoire compris entre 1032 et 65 535
  * 
  * @return Retourne le nombre aléatoire produit. 
  **/
uint16_t Transport::portAlea() {
	srand(time(NULL));
	uint16_t tmp = rand()%65535+1032;
	return tmp;
}

/**
  * @brief Permet de convertir des uint16_t en bitset de 16 bits.
  * 
  * @param val L'entier sur 16 bits que l'on souhaite convertir.
  * @return Le bitset de 16 bits produit.
  **/
std::bitset<16> Transport::convertir(const uint16_t& val) {  
	std::bitset<16> tmp(val);
	return tmp;
}

/**
  * @brief Permert de claculer le Checksum.
  * @param Ne Prend aucun parametre.
  * @return Ne retourne rien.
  **/
void Transport::calculerChecksum() {
    std::bitset<16> portSrc(m_PortSrc);
    std::bitset<16> portDest(m_PortDest);

    std::bitset<16> seqGauche, seqDroite;
    diviser(m_Seq, seqGauche, seqDroite);

    std::bitset<16> ack2Gauche, ack2Droite;
    diviser(m_Ack2, ack2Gauche, ack2Droite);

    int somme;
    somme = portSrc.to_ulong();
    somme += portDest.to_ulong();
    somme += m_cwnd.to_ulong();
    somme += m_Syn.to_ulong();
    somme += seqGauche.to_ulong();
    somme += seqDroite.to_ulong();
    somme += ack2Gauche.to_ulong();
    somme += ack2Droite.to_ulong();

    std::bitset<32> sommeBit(somme);
    std::bitset<16> retenuBit, sommeFinaleBit;
    diviser(sommeBit, retenuBit, sommeFinaleBit);

    int retenu, sommeFinale;
    retenu = retenuBit.to_ulong();
    sommeFinale = sommeFinaleBit.to_ulong();
    sommeFinale += retenu;    

    m_Checksum = std::bitset<16>(sommeFinale);
}

/**
  * @brief Verifie si tous les bits du Checksum sont a 1.
  * @param Ne prend aucun parametre.
  * @return Ne retourne rien.
  **/
void Transport::verifierChecksum() {

    if(m_Checksum.all()) {
      std::cout << "validé" << std::endl;
    }
    else {
      std::cout << "refusé" << std::endl;
    }
}

/**
  * @brief Permet d'encapsuler la couche Transport.
  * 
  * @return Une pile contenant toute les attributs de la classe Transport. 
  **/
std::stack<std::bitset<16>> Transport::encapsuler() {
    std::stack<std::bitset<16>> segment;
    segment.push(convertir(m_PortSrc));
    segment.push(convertir(m_PortDest));
    segment.push(m_Cwnd);
    segment.push(m_Checksum);
    segment.push(m_Syn);
    segment.push(m_Ack1);

    // On divise m_Seq en deux bitset de 16bits pour les push dans la pile.
    std::bitset<16> seqGauche, seqDroite;
    diviser(m_Seq, seqGauche, seqDroite);
    segment.push(seqGauche);
    segment.push(seqDroite);

    std::bitset<16> ack2Gauche, ack2Droite;
    diviser(m_Ack2, ack2Gauche, ack2Droite);
    segment.push(ack2Gauche);
    segment.push(ack2Droite);

    return segment;
}

/**
  * @brief Permet de desencapsuler la couche Transport.
  * 
  * @param segment Resultat de la desencapsulation de la couche Internet.
  * @return Un bitset de 16 qui est la données a transmettre. 
  **/
std::bitset<16> Transport::desencapsuler(std::stack<std::bitset<16>>& segment) {
    
    //
    std::bitset<16> ack2Droite = segment.top();
    segment.pop();
    std::bitset<16> ack2Gauche = segment.top();
    segment.pop();
    m_Ack2 = concat(ack2Droite, ack2Gauche);

    //
    std::bitset<16> seqDroite = segment.top();
    segment.pop();
    std::bitset<16> seqGauche = segment.top();
    segment.pop();
    m_Seq = concat(seqDroite, seqGauche);
    
    //
    m_Ack1 = segment.top();
    segment.pop();
    m_Syn = segment.top();
    segment.pop();
    m_Checksum = segment.top();
    segment.pop();
    m_Cwnd = segment.top();
    segment.pop();

    //
    m_PortDest = segment.top().to_ulong();
    segment.pop();
    m_PortSrc = segment.top().to_ulong();
    segment.pop();

    return std::bitset<16>(segment.top());
}
