/**

 * @file        Internet.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe Internet.
 * 
 * @author      Quentin GRUCHET
 * @author      Fadi MECHRI
 * @date        2021

 **/

#include "Internet.hpp"

/**
  * @brief Constructeur de la classe Internet
  **/
Internet::Internet() {
    m_IpSrc = ipMax;
    m_IpDest = ipMax;
    m_TTL.set();
    m_ProtocoleId.set();
    m_Checksum.set();
}

 /**
  * @brief Destructeur de la classe Internet.
  * 
  * Le destructeur est vide car tout est géré par le 'garbage collector'.
  **/
Internet::~Internet() {}

 /**
  * @brief Setter pour l'attribut de classe m_IpSrc.
  * 
  * @param src IP de départ souhaité.
  * @return void.
  **/
void Internet::setIpSrc(IPv4 src) {
    m_IpSrc = src;
}

 /**
  * @brief Getter pour l'attribut de classe m_IpSrc.
  * 
  * @return Référence vers l'attribut de classe m_IpSrc.
  **/
const IPv4& Internet::getIpSrc() const {
    return m_IpSrc;
}

 /**
  * @brief Setter pour l'attribut de classe m_IpSrc.
  * 
  * @param dest IP de destination souhaité.
  * @return void.
  **/
void Internet::setIpDest(IPv4 dest) {
    m_IpDest = dest;
}
 /**
  * @brief Getter pour l'attribut de classe m_IpDest.
  * 
  * @return Référence vers l'argument de classe m_IpDest.
  **/
const IPv4& Internet::getIpDest() const {
    return m_IpDest;
}

 /**
  * @brief Setter pour l'attribut de classe m_TTL.
  * 
  * @param ttl La valeur souhaité du TTL.
  * @return void.
  **/
void Internet::setTTL(const std::bitset<8>& ttl) {
    m_TTL = ttl;
}

 /**
  * @brief Getter pour l'attribut de classe m_TTL.
  * 
  * @return La valeur du TTL.
  **/
const std::bitset<8>& Internet::getTTL() const {
    return m_TTL;
}

 /**
  * @brief Setter pour l'attribut de classe m_ProtocoleId.
  * 
  * Ici, aucun argument est nécessaire. Nous utilisons toujours le protocole TCP donc son ID est toujours 6. 
  * 
  * @return void.
  **/
void Internet::setProtocoleId() {
    m_ProtocoleId = std::bitset<8> (6);
}

 /**
  * @brief Getter pour l'attribut de classe m_ProtocoleId.
  * 
  * @return La valeur de l'identifiant du protocole. 
  **/
const std::bitset<8>& Internet::getProtocoleId() const {
    return m_ProtocoleId;
}

const std::bitset<16>& Internet::getChecksum() const {
    return m_Checksum;
}

 /**
  * @brief Permet de convertir une IPv4 en un bitset de 32 bits pour encapsuler cette données.
  * 
  * On converti d'abord chaque champs de la structure IPv4 en chaine de caractère. 
  * Puis nous créeons un bitset de la concaténation de ces chaines de caractère. 
  * 
  * @param adresse L'IPv4 que l'on souhaite modifier.
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
  * @param ip L'adresse IP a remplir.
  * @param ipPartBa Premier bitset contenant les champs a et b de l'IP.
  * @param ipPartDC Second bitset contenant les champs c et d de l'IP.
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
  * @brief Permet de calculer le Checksum.
  * 
  * @return void.
  **/
void Internet::calculerChecksum() {

    // Etant donne la declaration d'un IPV4 m_IpSrc qui correpsond
    // à 4 bitset de 8, alors on declare deux bitset de 16: IpSrc1 et IpSrc2,
    // qui vont tous les deux prendre la concatenations de m_IpSrc.a, m_IpSrc.b
    // pour IpSrc1 et m_IpSrc.c, m_IpSrc.d pour IpSrc2.
    // Meme principe pour IPV4 IpDest.
    std::bitset<16> IpSrc1(concat(m_IpSrc.a, m_IpSrc.b));
    std::bitset<16> IpSrc2(concat(m_IpSrc.c, m_IpSrc.d));
    std::bitset<16> IpDest1(concat(m_IpDest.a, m_IpDest.b));
    std::bitset<16> IpDest2(concat(m_IpDest.c, m_IpDest.d));
    std::bitset<16> TTL(m_TTL.to_ulong());
    std::bitset<16> protocoleId(m_ProtocoleId.to_ulong());
	
    // Declaration de la variable somme 
    // qui va contenir l'addition des differents bitset.
    int somme;
    somme = IpSrc1.to_ulong();
    somme += IpSrc2.to_ulong();
    somme += IpDest1.to_ulong();
    somme += IpDest2.to_ulong();
    somme += TTL.to_ulong();
    somme += protocoleId.to_ulong();
    
    // Declaration de sommeBit en bitset de 32
    // qui va stocker la valeur de somme dans celle-ci
    // qui sera ensuite diviser en deux bitsets
    // pour la retenuBit et sommeFinalBit.
    std::bitset<32> sommeBit(somme);
    std::bitset<16> retenuBit, sommeFinaleBit;
    diviser(sommeBit, retenuBit, sommeFinaleBit);

    // On va attribue a la variable retenu la valeur de retenuBit
    // puis l'additionner a la sommeFinale, pour la stocker dans m_Checksum.
    int retenu = retenuBit.to_ulong();
    int sommeFinale = sommeFinaleBit.to_ulong();
    sommeFinale += retenu;    

    m_Checksum = std::bitset<16>(sommeFinale);
}

 /**
  * @brief Permet de verifier si tous les bits du Checksum sont a 1.
  *
  * @return void.
  **/
void Internet::verifierChecksum() {
    
    // La fonction all() va verifier si tous les bits sont egales a 1.
    if (m_Checksum.all()) {
      std::cout << "validé" << std::endl;
    }
    else {
      std::cout << "refusé" << std::endl;
    }
}


 /**
  * @brief Permet l'encapsulation de la couche Internet.
  * 
  * @param segment Resultat de l'encapsulation de la couche Transport.
  * @return Resultat de l'encapsulation. Contient donc la couche Transport + la couche Internet.
  **/
 std::stack<std::bitset<16>> Internet::encapsuler(std::stack<std::bitset<16>>& segment) {
    segment.emplace(concat(m_IpSrc.a, m_IpSrc.b));
    segment.emplace(concat(m_IpSrc.c, m_IpSrc.d));
    segment.emplace(concat(m_IpDest.a, m_IpDest.b));
    segment.emplace(concat(m_IpDest.c, m_IpDest.d));
    segment.emplace(concat(m_TTL, m_ProtocoleId));
    segment.emplace(m_Checksum);

    return segment;
 }

 /**
  * @brief Permet la desencapsulation de la couche Internet.
  * 
  * @param paquet Resultat de l'encapsulation de la couche Physique.
  * @return Resultat de la desencapsulation. Contient donc uniquement la couche Transport.
  **/
 std::stack<std::bitset<16>> Internet::desencapsuler(
   std::stack<std::bitset<16>>& paquet)
{
    //Extraction du Checksum
    m_Checksum = paquet.top();
    paquet.pop();

    //Extraction du TTL et du Protocole ID
    std::bitset<8> ttl, pId;
    diviser(paquet.top(), ttl, pId);
    m_TTL = ttl;
    m_ProtocoleId = pId;
    paquet.pop();

    //Extraction de l'ip de destination
    std::bitset<8> ipDestA, ipDestB, ipDestC, ipDestD;
    diviser(paquet.top(), ipDestC, ipDestD);
    m_IpDest.c = ipDestC;
    m_IpDest.d = ipDestD;
    paquet.pop();
    diviser(paquet.top(), ipDestA, ipDestB);
    m_IpDest.a = ipDestA;
    m_IpDest.b = ipDestB;
    paquet.pop();

    //Extraction de l'ip source
    std::bitset<8> ipSrcA, ipSrcB, ipSrcC, ipSrcD;
    diviser(paquet.top(), ipSrcC, ipSrcD);
    m_IpSrc.c = ipSrcC;
    m_IpSrc.d = ipSrcD;
    paquet.pop();
    diviser(paquet.top(), ipSrcA, ipSrcB);
    m_IpSrc.a = ipSrcA;
    m_IpSrc.b = ipSrcB;
    paquet.pop();

    return paquet;
}

/**
 * @brief Surcharge l'opérateur d'affichage pour afficher tout les attributs de classe.
 * 
 * @param flux Permet de d'afficher dans le terminal.
 * @param coucheInt La couche a afficher.
 **/
std::ostream& operator<<(std::ostream& flux, const Internet& coucheInt) {
    flux << "m_IpSrc : " << coucheInt.getIpSrc() << std::endl;
    flux << "m_IpDest : " << coucheInt.getIpDest() << std::endl;
    flux << "m_TTL : " << coucheInt.getTTL().to_ulong() << std::endl;
    flux << "m_ProtocoleId : " << coucheInt.getProtocoleId().to_ulong() << std::endl;
    flux << "m_Checksum : " << coucheInt.getChecksum().to_ulong() << std::endl;

    return flux;
}
