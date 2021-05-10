#ifndef FENETRERESEAU_H
#define FENETRERESEAU_H

#include "ChoixReseau.hpp"
#include "DonneeReseau.hpp"

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>

class FenetreReseau : public QHBoxLayout
{
Q_OBJECT
    private:
        // Attributs
        ChoixReseau* m_F1;
        DonneeReseau* m_F2;

    public :
        // Constructeur
        FenetreReseau();

        // Destructeur
        ~FenetreReseau();

};

#endif // FENETRERESEAU_H
