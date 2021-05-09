/**
 * transport.cpp : Vous trouverez ici toutes les fonctions implemente pour la classe Transport.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#include "Transport.hpp"

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
Transport::Transport() {
	
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
Transport::~Transport() {

}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setPortSrc(const uint16_t& src) {
    m_PortSrc = src;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
uint16_t &Transport::getPortSrc() {
    return m_PortSrc;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
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
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
uint16_t &Transport::getPortDest() {
    return m_PortDest;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setCwnd(const std::bitset<16>& cwnd) {
    m_Cwnd = cwnd;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<16> &Transport::getCwnd() {
    return m_Cwnd;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setChecksum(const std::bitset<16>& checksum) {
    m_Checksum = checksum;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<16>& Transport::getChecksum() {
    return m_Checksum;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setSyn(const std::bitset<16>& syn) {
    m_Syn = syn;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<16> &Transport::getSyn() {
    return m_Syn;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setAck1(const std::bitset<16>& ack1) {
    m_Ack1 = ack1;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<16> &Transport::getAck1() {
    return m_Ack1;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setSeq(const std::bitset<32>& numSeq) {
    m_Seq = numSeq;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<32>& Transport::getSeq() {
    return m_Seq;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::setAck2(const std::bitset<32>& ack2) {
    m_Ack2 = ack2;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<32> &Transport::getAck2() {
    return m_Ack2;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
uint16_t Transport::portAlea() {
	srand(time(NULL));
	uint16_t tmp = rand()%65535+1032;
	return tmp;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<16> Transport::convertirPortEnBit(const uint16_t& val) {  
	std::bitset<16> tmp(val);
	return tmp;
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::calculerChecksum() {

}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Transport::verifierChecksum() {

}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::stack<std::bitset<16>> Transport::encapsuler() {
    std::stack<std::bitset<16>> segment;
    segment.push(convertirPortEnBit(m_PortSrc));
    segment.push(convertirPortEnBit(m_PortDest));
    segment.push(m_Cwnd);
    segment.push(m_Checksum);
    segment.push(m_Syn);
    segment.push(m_Ack1);

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
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
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