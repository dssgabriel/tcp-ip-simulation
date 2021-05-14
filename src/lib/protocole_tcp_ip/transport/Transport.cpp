/**

 * @file        Transport.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe Transport.
 * 
 * @author      Quentin GRUCHET
 * @author      Fadi MECHRI
 * @date        2021

 **/

#include "Transport.hpp"

/**
  * @brief Constructeur de la classe Transport.
  * 
  * Le constructeur est vide car nous utilisons les setters pour initialiser les differents paramètres.
  * 
  * @return NULL. 
  **/
Transport::Transport() {}

/**
  * @brief Destucteur de la classe Transport.
  * 
  * Le destructeur est vide car tout est géré par le 'garbage collector'.
  * 
  * @return NULL.
  **/
Transport::~Transport() {}

/**
  * @brief Setter de l'attribut de classe m_PortSrc.
  * 
  * @param src La valeur du port source souhaité.
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
const uint16_t &Transport::getPortSrc() const {
    return m_PortSrc;
}

/**
  * @brief Setter de l'attribut m_PortDest de la classe Transport
  * 
  * @param num La structure contenant le type de fichier que l'on va envoyer.
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
const uint16_t &Transport::getPortDest() const {
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
const std::bitset<16> &Transport::getCwnd() const {
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
const std::bitset<16>& Transport::getChecksum() const {
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
const std::bitset<16> &Transport::getSyn() const {
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
const std::bitset<16> &Transport::getAck1() const {
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
const std::bitset<32>& Transport::getSeq() const {
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
const std::bitset<32> &Transport::getAck2() const {
    return m_Ack2;
}

/**
  * @brief Permet de produire un nombre aléatoire compris entre 1032 et 65 535
  * 
  * @return Retourne le nombre aléatoire produit. 
  **/
uint16_t Transport::portAlea() {
	return rand()%65535+1032;
}

/**
  * @brief Permert de claculer le Checksum.
  * 
  * @return void.
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
    somme += m_Cwnd.to_ulong();
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
  * 
  * @return void.
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
std::stack<std::bitset<16>> Transport::encapsuler(std::bitset<16> donnee) {
    std::stack<std::bitset<16>> segment;
    segment.emplace(donnee);
    segment.emplace(std::bitset<16>(m_PortSrc));
    segment.emplace(std::bitset<16>(m_PortDest));
    segment.emplace(m_Cwnd);
    segment.emplace(m_Checksum);
    segment.emplace(m_Syn);
    segment.emplace(m_Ack1);

    // On divise m_Seq en deux bitset de 16bits pour les emplace dans la pile.
    std::bitset<16> seqGauche, seqDroite;
    diviser(m_Seq, seqGauche, seqDroite);
    segment.emplace(seqGauche);
    segment.emplace(seqDroite);

    std::bitset<16> ack2Gauche, ack2Droite;
    diviser(m_Ack2, ack2Gauche, ack2Droite);
    segment.emplace(ack2Gauche);
    segment.emplace(ack2Droite);

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

std::ostream& operator<<(std::ostream& flux, const Transport& coucheTrans) {
    flux << "m_PortSrc : " << coucheTrans.getPortSrc() << std::endl;
    flux << "m_PortDest : " << coucheTrans.getPortDest() << std::endl;
    flux << "m_Cwnd : " << coucheTrans.getCwnd();
    flux << ", " << coucheTrans.getCwnd().to_ulong() << std::endl;
    flux << "m_Checksum : " << coucheTrans.getChecksum();
    flux << ", " << coucheTrans.getChecksum().to_ulong() << std::endl;
    flux << "m_Syn : " << coucheTrans.getSyn();
    flux << ", " << coucheTrans.getSyn().to_ulong() << std::endl;
    flux << "m_Ack1 : " << coucheTrans.getAck1();
    flux << ", " << coucheTrans.getAck1().to_ulong() << std::endl;
    flux << "m_Seq : " << coucheTrans.getSeq();
    flux << ", " << coucheTrans.getSeq().to_ulong() << std::endl;
    flux << "m_Ack2 : " << coucheTrans.getAck2();
    flux << ", " << coucheTrans.getAck2().to_ulong() << std::endl;

    return flux;
}