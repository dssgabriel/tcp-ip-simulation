/**
 * Internet.cpp : Vous trouverez ici toutes les fonctions implemente pour la classe Internet.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#include "Internet.hpp"

/**
  * @brief Constructeur de la classe Internet
  * 
  * Le constructeur est vide car nous utilisons les setters pour initialiser les differents paramètres.
  * 
  * @return NULL.
  **/
Internet::Internet() {
}

 /**
  * @brief Destructeur de la classe Internet.
  * 
  * Le destructeur est vide car tout est géré par le 'garbage collector'.
  * 
  * @return NULL.
  **/
Internet::~Internet() {

}

 /**
  * @brief Setter pour l'argument de classe m_IpSrc.
  * 
  * @param 1 IPv4 src : IP de départ souhaité.
  * @return void.
  **/
void Internet::setIpSrc(IPv4 src) {
    m_IpSrc = src;
}

 /**
  * @brief Getter pour l'argument de classe m_IpSrc.
  * 
  * @return Référence vers l'attribut de classe m_IpSrc.
  **/
IPv4& Internet::getIpSrc() {
    return m_IpSrc;
}

 /**
  * @brief Setter pour l'argument de classe m_IpSrc.
  * 
  * @param dest : IP de destination souhaité.
  * @return void.
  **/
void Internet::setIpDest(IPv4 dest) {
    m_IpDest = dest;
}
 /**
  * @brief Getter pour l'argument de classe m_IpDest.
  * 
  * @return Référence vers l'argument de classe m_IpDest.
  **/
IPv4& Internet::getIpDest() {
    return m_IpDest;
}

 /**
  * @brief Setter pour l'argument de classe m_TTL.
  * 
  * @param ttl : La valeur souhaité du TTL.
  * @return void.
  **/
void Internet::setTTL(const std::bitset<8>& ttl) {
    m_TTL = ttl;
}

 /**
  * @brief Getter pour l'argument de classe m_TTL.
  * 
  * @return La valeur du TTL.
  **/
std::bitset<8> &Internet::getTTL() {
    return m_TTL;
}

 /**
  * @brief Setter pour l'argument de classe m_ProtocoleId.
  * 
  * Ici, aucun argument est nécessaire. Nous utilisons toujours le protocole TCP donc son ID est toujours 6. 
  * 
  * @return void.
  **/
void Internet::setProtocoleId() {
    m_ProtocoleId = std::bitset<8> (6);
}

 /**
  * @brief Getter pour l'argument de classe m_ProtocoleId.
  * 
  * @return La valeur de l'identifiant du protocole. 
  **/
std::bitset<8> &Internet::getProtocoleId() {
    return m_ProtocoleId;
}

 /**
  * @brief Permet de convertir une IPv4 en un bitset de 32 bits pour encapsuler cette données.
  * 
  * On converti d'abord chaque champs de la structure IPv4 en chaine de caractère. 
  * Puis nous créeons un bitset de la concaténation de ces chaines de caractère. 
  * 
  * @param adresse : L'IPv4 que l'on souhaite modifier.
  * @return Le bitset obtenue après conversion.
  **/
std::bitset<32> Internet::convertir(const IPv4& adresse) {
	std::string s1 = adresse.a.to_string();
	std::string s2 = adresse.b.to_string();
	std::string s3 = adresse.c.to_string();
	std::string s4 = adresse.d.to_string();

	return std::bitset<32>(s1 + s2 + s3 + s4);
}

 /**
  * @brief Permet de convertir deux bitset de 16 bits en une structure IPv4.
  * 
  * Après désencapsulation, les adresses IP sont contenues dans deux std::bitset<16> ou chaque 8 bits représente un champ de l'IP.
  * Cette fonction permet donc de diviser ces bitset en deux, pour remplir l'IP.
  * 
  * @param ip : L'adresse IP a remplir.
  * @param ipPartBa : Premier bitset contenant les champs a et b de l'IP.
  * @param ipPartDC : Second bitset contenant les champs c et d de l'IP.
  **/
void Internet::convertir(IPv4& ip,
    const std::bitset<16>& ipPartBA, 
    const std::bitset<16>& ipPartDC)
{
    // Decoupage, et convertion en IPv4.
    diviser(ipPartBA, ip.b, ip.a);
    diviser(ipPartDC, ip.d, ip.c);
}

 /**
  * @brief 
  * @param
  * @return void
  **/
void Internet::calculerChecksum() {
    // TODO
}

 /**
  * @brief 
  * @param
  * @return void
  **/
void Internet::verifierChecksum() {
    // TODO
}

 /**
  * @brief Permet l'encapsulation de la couche Internet.
  * 
  * @param segment : Resultat de l'encapsulation de la couche Transport.
  * @return Resultat de l'encapsulation. Contient donc la couche Transport + la couche Internet.
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
  * @brief Permet la desencapsulation de la couche Internet.
  * 
  * @param paquet : Resultat de l'encapsulation de la couche Physique.
  * @return Resultat de la desencapsulation. Contient donc uniquement la couche Transport.
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