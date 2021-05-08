/**
 * Physique.cpp : Vous trouverez ici toutes les fonctions implemente pour la classe Physique.
 * Auteur : Quentin GRUCHET & Fadi MECHRI.
 **/

#include "Physique.hpp"

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
Physique::Physique(){
    
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
Physique::~Physique() {

}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Physique::setMacSrc(MAC src) {
    m_SrcMac = src;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
MAC Physique::getMacSrc() {
    return m_SrcMac;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
void Physique::setMacDest(MAC dest) {
    m_DestMac = dest;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
MAC Physique::getMacDest() {
    return m_DestMac;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::bitset<48> Physique::convertirMacEnBits(const MAC& adresse) {
	std::string s1 = adresse.a.to_string();
	std::string s2 = adresse.b.to_string();
	std::string s3 = adresse.c.to_string();
	std::string s4 = adresse.d.to_string();
	std::string s5 = adresse.e.to_string();
	std::string s6 = adresse.f.to_string();
	return std::bitset<48>(s1 + s2 + s3 + s4 + s5 + s6);
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
MAC Physique::convetirBitsEnMac(const std::bitset<16>& adrPartAB, 
    const std::bitset<16>& adrPartCD, const std::bitset<16>& adrPartEF) 
{
  MAC mac;

  //
  size_t i;
  for(i = 0; i < 8; ++i) {
    mac.a[i] = adrPartAB[i];
  }
  for(i = 0; i < 8; ++i) {
    mac.b[i] = adrPartAB[8+i];
  }
  for(i = 0; i < 8; ++i) {
    mac.c[i] = adrPartCD[i];
  }
  for(i = 0; i < 8; ++i) {
    mac.d[i] = adrPartCD[8+i];
  }
  for(i = 0; i < 8; ++i) {
    mac.e[i] = adrPartEF[i];
  }
  for(i = 0; i < 8; ++i) {
    mac.f[i] = adrPartEF[8+i];
  }
  return mac;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::stack<std::bitset<16>> Physique::decoupageMac(const std::bitset<48>& adresse) {
  std::stack<std::bitset<16>> pile;
  std::bitset<16> eltPile;

  //
  size_t i;
  size_t posAdr = 0;
  for(i = 0; i < 16; ++i) {
    eltPile[i] = adresse[posAdr];
    posAdr++;
  }
  pile.push(eltPile);
  for(i = 0; i < 16; ++i) {
    eltPile[i] = adresse[posAdr];
    posAdr++;
  }
  pile.push(eltPile);
  for(i = 0; i < 16; ++i) {
    eltPile[i] = adresse[posAdr];
    posAdr++;
  }
  pile.push(eltPile);

  return pile;
}

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
 std::stack<std::bitset<16>> Physique::encapsuler(std::stack<std::bitset<16>>& paquet) {
    paquet.push(concat(m_SrcMac.a, m_SrcMac.b));
    paquet.push(concat(m_SrcMac.c, m_SrcMac.d));
    paquet.push(concat(m_SrcMac.e, m_SrcMac.f));
    paquet.push(concat(m_DestMac.a, m_DestMac.b));
    paquet.push(concat(m_DestMac.c, m_DestMac.d));
    paquet.push(concat(m_DestMac.e, m_DestMac.f));

    return paquet;
 }

 /**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
std::stack<std::bitset<16>> Physique::desencapsuler(std::stack<std::bitset<16>>& trame) {
    for (size_t i = 0; i < 6; i++)
    {
        trame.pop();
    }

    return trame;
}