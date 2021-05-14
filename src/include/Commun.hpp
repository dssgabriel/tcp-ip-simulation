#pragma once

#include <bitset>
#include <string>

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
template <size_t N>
void diviser(const std::bitset <N>& original,
            std::bitset <N/2>& gauche, std::bitset <N/2>& droite)
{
	droite = std::bitset<N/2> ((original).to_ulong());
	gauche = std::bitset<N/2> ((original >> N/2).to_ulong());
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
template <size_t N>
void diviser(std::bitset <N> original, std::bitset <N/3>& gauche,
            std::bitset <N/3>& milieu, std::bitset <N/3>& droite)
{
	droite = std::bitset<N/3> ((original).to_ulong());
	milieu = std::bitset<N/3> ((original >>= N/3).to_ulong());
	gauche = std::bitset<N/3> ((original >> N/3).to_ulong());
}

/**
  * Description :
  * Fonction :
  * Parametres : 
  * Sortie :
  **/
template <size_t N1, size_t N2 >
std::bitset<N1 + N2> concat(const std::bitset <N1> b1,
            const std::bitset <N2> b2)
{
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
template <size_t N>
void inverser(std::stack<std::bitset<N>> &pile) {
    std::stack<std::bitset<N>> pileInv;

    for(size_t i = 0; i < pile.size(); ++i) {
        pileInv.push(pile.top());
        pile.pop();
    }
}