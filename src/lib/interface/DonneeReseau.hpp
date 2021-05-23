/**
 * @file        DonneeReseau.hpp
 * @brief       Déclaration de la classe DonneeReseau.
 * 
 * @author      Johann RAMANANDRAISIORY 
 * @date        2021
 **/

#ifndef DONNEERESEAU_H
#define DONNEERESEAU_H

#include "AffichageReseau.hpp"
#include "ConfigReseau.hpp"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

class DonneeReseau : public QVBoxLayout
{
Q_OBJECT

    public :
        // Constructeur
        DonneeReseau();
        // Destructeur
        ~DonneeReseau();

};

#endif // DONNEERESEAU_H
