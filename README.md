# IN608 - Projet : Simulation du protocole TCP/IP

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-qt.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/not-a-bug-a-feature.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/powered-by-black-magic.svg)](http://forthebadge.com)

> "There are some people who imagine that older adults don't know how to use the internet. My immediate reaction is, "I've got news for you, we invented it."

<p align="right">
  Vinton Gray Cerf, co-créateur du protocole TCP/IP.
</p>

--------
## Introduction
Ce projet est réalisé pour le module IN608 de L3 Informatique, au sein de l’Université de Versailles - Saint-Quentin-en-Yvelines, et encadré par Mme Leila KLOUL.

L’objectif de celui-ci est de créer une application à but pédagogique simulant le protocole TCP/IP au travers d'une interface graphique.
Pour cela, l’application présentera toutes les étapes que subit une donnée afin de pouvoir transitée sur un réseau, puis d'etre traitée par son destinataire.

Le rendu final sera supporté par tous les systèmes d’exploitation basé sur le noyau Linux et offrira un moyen de compilation simple (`cmake`).

## Installation
Pour installer cette application sur votre ordinateur, il vous suffit de cloner ce dépôt GitHub sur votre machine.

Depuis un terminal, exécuter la commande suivante :
```sh
git clone https://github.com/dssgabriel/in608-tcp_ip_simulation
```

## Compilation

Afin de compiler l'application, vous devrez vous assurez que les logiciels suivants sont installes sur votre machine :
- Un compilateur C++ tel que `g++` (version 7.1 ou supérieure) ou `clang++` (version 6.0 ou supérieure)
- L'outil de compilation CMake (version 3.8 ou supérieure)
- Les modules `Qt Core`, `Qt Widgets` et `Qt Charts` de l'environnement de développement d'interface graphique Qt (version 5)

Pour exécuter l'application, il vous faudra exécuter l'ensemble des commandes suivantes à la racine du projet :
```sh
cd build/

./Sim-TCP_IP
```

Si vous désirez recompiler le programme dans sa globalité, il vous faut taper la commande suivante à la racine du projet :
```sh
./build.sh
 ```

-------

## Contributeurs

**Florian Cambresy** _alias_ [EXsky51](https://github.com/EXsky51)

**Jean-Christophe Chalaud** _alias_ [Jean-Christophe04](https://github.com/Jean-Christophe04)

**Gabriel Dos Santos** _alias_ [dssgabriel](https://github.com/dssgabriel)

**Quentin Gruchet** _alias_ [QGruchet](https://github.com/QGruchet)

**Mickaël Le Denmat** _alias_ [m27bay](https://github.com/m27bay) 

**Raphaël Lin** _alias_ [uvsq21802498](https://github.com/uvsq21802498)

**Fadi Mechri** _alias_ [Mfadi](https://github.com/uvsq21603504)

**Johann Ramanandraitsiory** _alias_ [uvsq21805057](https://github.com/uvsq21805057)
