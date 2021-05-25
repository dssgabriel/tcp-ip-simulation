/**
 * @file ConfigReseau.hpp
 * @author Jean-Christophe
 * @brief Vous trouverez ici la declaration de la classe ConfigReseau
 * 
 * @date 2021
 * 
 */
#ifndef CONFIGRESEAU_H
#define CONFIGRESEAU_H

#include "Contexte.hpp"

#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>

class ConfigReseau : public QHBoxLayout
{
Q_OBJECT
    private:
        // Attributs
        ConfigReseau();

        QTextEdit* m_FenetreDonnee;

    public :
        // Singleton
        static ConfigReseau& GetInstance() {
            static ConfigReseau singleton;
            return singleton;
        }

        // Méthodes de copie
        ConfigReseau(ConfigReseau&) = delete;
        void operator=(ConfigReseau&) = delete;

        // Destructeur
        ~ConfigReseau();

        //Methodes
        void initialiserTexte();
        void rafraichirTexte();
};

#endif // CONFIGRESEAU_H
