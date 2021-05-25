/**
 * @file Commun.hpp
 * @brief Vous trouverez ici des fonctions de manipulations de std::bitset
 * @date 2021-05-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <iostream>

/**
 * @brief Definition de couleur pour l'affichage dans le terminal.
 *
 */
#define GRAS     "\e[1m"
#define ITALIQUE "\e[3m"
#define SOULIGNE "\e[4m"
#define RAYE     "\e[9m"

#define ROUGE    "\e[31m"
#define VERT     "\e[32m"
#define JAUNE    "\e[33m"
#define BLUE     "\e[34m"
#define MAGENTA  "\e[35m"
#define CYAN     "\e[36m"

#define RESET    "\e[0m"

#define DEBUG 0

// NE PAS METTRE DANS UN CPP //

/**
 * @brief Permet de separer un bitset en deux bitset de taille egale.
 *
 * @param orginal Le bitset que l'on veut diviser en deux.
 * @param gauche Il s'agit du bitset qui va contenir la partie gauche de original.
 * @param droite Il s'agit du bitset qui va contenir la partie droite de original.
 **/
template <size_t N>
void diviser(const std::bitset <N>& original,
    std::bitset <N/2>& gauche, std::bitset <N/2>& droite)
{
	droite = std::bitset<N/2> ((original).to_ulong());
	gauche = std::bitset<N/2> ((original >> N/2).to_ulong());
}

/**
 * @brief Permet de separer un bitset en trois bitset de taille egale.
 *
 * @param orginal Le bitset que l'on veut diviser en trois.
 * @param gauche Il s'agit du bitset qui va contenir la partie gauche de original.
 * @param droite Il s'agit du bitset qui va contenir la partie droite de original.
 * @param milieur Il d'agit du bitset qui va contenir la partie central de original.
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
 * @brief Permet de concatener deux bitsets.
 *
 * @param orginal Le bitset que l'on veut diviser en deux.
 * @param gauche Le premier bitset que l'on veut concatener.
 * @param droite Le second bitset que l'on veut concatener.
 * @return Un std::bitset de tailles egales a la somme des details de deux bitset a concatener.
 **/
template <size_t N1, size_t N2>
std::bitset<N1 + N2> concat(const std::bitset <N1> gauche,
    const std::bitset <N2> droite)
{
    std::string gaucheStr = gauche.to_string();
    std::string droiteStr = droite.to_string();
    return std::bitset <N1 + N2>(gaucheStr + droiteStr);
}

void afficher(std::stack<std::bitset<16>> pile);

void afficher(std::queue<std::stack<std::bitset<16>>> file);

void afficher(std::deque<std::stack<std::bitset<16>>> doubleFile);
