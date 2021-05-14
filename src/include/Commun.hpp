#pragma once

#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <iostream>

// NE PAS METTRE DANS UN CPP

template <size_t N>
void diviser(const std::bitset <N>& original,
    std::bitset <N/2>& gauche, std::bitset <N/2>& droite)
{
	droite = std::bitset<N/2> ((original).to_ulong());
	gauche = std::bitset<N/2> ((original >> N/2).to_ulong());
}

template <size_t N>
void diviser(std::bitset <N> original, std::bitset <N/3>& gauche,
    std::bitset <N/3>& milieu, std::bitset <N/3>& droite)
{
    droite = std::bitset<N/3> ((original).to_ulong());
    milieu = std::bitset<N/3> ((original >>= N/3).to_ulong());
    gauche = std::bitset<N/3> ((original >> N/3).to_ulong());
}

template <size_t N1, size_t N2>
std::bitset<N1 + N2> concat(const std::bitset <N1> b1,
    const std::bitset <N2> b2)
{
    std::string s1 = b1.to_string();
    std::string s2 = b2.to_string();
    return std::bitset <N1 + N2>(s1 + s2);
}

template <size_t N>
void afficher(std::stack<std::bitset<N>> pile) {
    std::cout << "debut stack\n";
    while (!pile.empty()) {
        std::cout << "(" << pile.top().to_string() << ") = (";
        std::cout << pile.top().to_ulong() << ")" << std::endl;
        pile.pop();
    }
    std::cout << "fin stack\n";
}

template <size_t N>
void afficher(std::queue<std::stack<std::bitset<N>>*> file) {
    std::cout << "debut queue\n";
    while (!file.empty()) {
        afficher(*file.front());
        file.pop();
    }
    std::cout << "fin queue\n";
}