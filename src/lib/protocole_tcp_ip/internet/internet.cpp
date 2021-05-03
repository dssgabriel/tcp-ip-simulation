/**
 * internet.cpp : Vous trouverez ici toutes les fonctions implemente pour la classe Internet.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#include "internet.hpp"

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
template <size_t N1, size_t N2 >
std::bitset<N1 + N2> concat(const std::bitset <N1> b1, const std::bitset <N2> b2){
    std::string s1 = b1.to_string();
    std::string s2 = b2.to_string();
    return std::bitset <N1 + N2>(s1 + s2);
}

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
void Internet::setProtocoleId(const std::bitset<8>& protocoleId) {
    m_ProtocoleId = protocoleId;
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
std::bitset<32> Internet::convertirIpEnBits(const IPv4& adresse) {
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
 std::stack<std::bitset<16>> Internet::desencapsuler(std::stack<std::bitset<16>>& paquet) {

    std::bitset<16> m_Checksum = paquet.top();
    paquet.pop();
    paquet.pop();
    for (size_t i = 0; i < 8; i++)
    {
        paquet.pop();
    }
    
    return paquet;
}