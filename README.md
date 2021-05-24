# IN608 - Projet : Simulation du protocole TCP/IP

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-qt.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/not-a-bug-a-feature.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](http://forthebadge.com)  [![forthebadge](https://forthebadge.com/images/badges/uses-brains.svg)](http://forthebadge.com)

## Introduction
Ce projet est réalisé pour le module IN608 de L3 Informatique, au sein de l’Université de Versailles - Saint-Quentin-en-Yvelines, et encadré par Mme Leila KLOUL.

L’objectif de celui-ci est de créer une application à but pédagogique simulant le protocole TCP/IP au travers d'une interface graphique.
Pour cela, l’application présentera toutes les étapes que subit une donnée afin de pouvoir transitée sur un réseau, puis d'etre traitée par son destinataire.

Le rendu final sera supporté par tous les systèmes d’exploitation basé sur le noyau Linux et offrira un moyen de compilation simple (`cmake`).

## Installation
Pour installer cette application sur votre ordinateur, il vous suffit de cloner ce dépot GitHub sur votre machine.

Depuis un terminal, exécuter la commande suivante :
```sh
git clone https://github.com/dssgabriel/in608-tcp_ip_simulation
```

## Compilation
### Dependences
Afin de compiler l'application, vous devrez vous assurez que les logiciels suivants sont installes sur votre machine :
- Un compilateur C++ tel que `g++` (version 7.1 ou supérieure) ou `clang++` (version 6.0 ou supérieure)
- L'outil de compilation CMake (version 3.8 ou supérieure)
- Les modules `Qt Core`, `Qt Widgets` et `Qt Charts` de l'environnement de développement d'interface graphique Qt (version 5)

Pour compiler et exécuter l'application, il vous suffit de taper la commande suivante à la racine du depot cloné :
```sh
./build.sh
```

# Auteurs

CAMBRESY Florian
CHALAUD Jean-Christophe
DOS SANTOS Gabriel
GRUCHET Quentin
LE DENMAT Mickaël
LIN Raphaël
MECHRI Fadi
RAMANANDRAITSIORY Johann
