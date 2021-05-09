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
Physique::Physique() {
    
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
std::bitset<48> Physique::convertir(const MAC& adresse) {
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
MAC Physique::convetir(const std::bitset<16>& adrPartBA, 
    const std::bitset<16>& adrPartDC, const std::bitset<16>& adrPartFE) 
{
  // Initialisation de l'adress MAC.
  MAC mac;

  //
  std::bitset<8> gauche, droite;

  diviser(adrPartBA, droite, gauche);
  mac.a = gauche;
  mac.b = droite;

  diviser(adrPartDC, droite, gauche);
  mac.c = gauche;
  mac.d = droite;

  diviser(adrPartFE, droite, gauche);
  mac.e = gauche; 
  mac.f = droite;

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