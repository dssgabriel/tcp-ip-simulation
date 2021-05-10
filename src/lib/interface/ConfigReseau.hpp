#ifndef CONFIGRESEAU_H
#define CONFIGRESEAU_H

#include <QApplication>
#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>

class ConfigReseau : public QHBoxLayout
{
Q_OBJECT
    private:
        // Attributs
        QTextEdit* m_FenetreDonnee;

    public :
        // Constructeur
        ConfigReseau();

        // Destructeur
        ~ConfigReseau();

        /*//Methodes
        void initialiserTexte();
        void rafraichirTexte();*/
};

#endif // CONFIGRESEAU_H
