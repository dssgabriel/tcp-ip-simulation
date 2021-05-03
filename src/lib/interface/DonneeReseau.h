#ifndef DONNEERESEAU_H
#define DONNEERESEAU_H

#include "AffichageReseau.h"
#include "ConfigReseau.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

class DonneeReseau : public QVBoxLayout
{
Q_OBJECT
    private:
        // Attributs
        AffichageReseau* m_F1;

        ConfigReseau* m_F2;

    public :
        // Constructeur
        DonneeReseau();
        // Destructeur
        ~DonneeReseau();
};

#endif // DONNEERESEAU_H
