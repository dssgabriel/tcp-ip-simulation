/**
 * internet.cpp : Vous trouverez ici toutes les fonctions implemente pour la classe Internet.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#include "Internet.hpp"

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
Internet::Internet() {

}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
Internet::~Internet() {

}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Internet::setIpSrc(IPv4 src) {
    m_IpSrc = src;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
IPv4& Internet::getIpSrc() {
    return m_IpSrc;
}

  /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Internet::setIpDest(IPv4 dest) {
    m_IpDest = dest;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
IPv4& Internet::getIpDest() {
    return m_IpDest;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Internet::setTTL(const std::bitset<8>& ttl) {
    m_TTL = ttl;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<8> &Internet::getTTL() {
    return m_TTL;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Internet::setProtocoleId() {
    m_ProtocoleId = std::bitset<8> (6);
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<8> &Internet::getProtocoleId() {
    return m_ProtocoleId;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<32> Internet::convertir(const IPv4& adresse) {
	std::string s1 = adresse.a.to_string();
	std::string s2 = adresse.b.to_string();
	std::string s3 = adresse.c.to_string();
	std::string s4 = adresse.d.to_string();
	return std::bitset<32>(s1 + s2 + s3 + s4);
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
IPv4& convertir(const std::bitset<16>& ipPartBA, 
    const std::bitset<16>& ipPartDC)
{
    // Initialisation.
    IPv4 ip;

    // Decoupage, et convertion en IPv4.
    diviser(ipPartBA, ip.b, ip.a);
    diviser(ipPartDC, ip.d, ip.c);

    return ip;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Internet::calculerChecksum() {

}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Internet::verifierChecksum() {

}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
 std::stack<std::bitset<16>> Internet::encapsuler(std::stack<std::bitset<16>>& segment) {
    segment.push(concat(m_IpSrc.a, m_IpSrc.b));
    segment.push(concat(m_IpSrc.c, m_IpSrc.d));
    segment.push(concat(m_IpDest.a, m_IpDest.b));
    segment.push(concat(m_IpDest.c, m_IpDest.d));
    segment.push(concat(m_TTL, m_ProtocoleId));
    segment.push(m_Checksum);

    return segment;
 }

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
 std::stack<std::bitset<16>> Internet::desencapsuler(
   std::stack<std::bitset<16>>& paquet)
{
    m_Checksum = paquet.top();
    paquet.pop();
    paquet.pop();
    for (size_t i = 0; i < 8; i++)
    {
        paquet.pop();
    }
    
    return paquet;
}