#ifndef CHOIXRESEAU_H
#define CHOIXRESEAU_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QFrame>
#include "Contexte.hpp"

class ChoixReseau : public QVBoxLayout
{
Q_OBJECT
    private :
        // Attributs
        QComboBox* m_Depart;
        QComboBox* m_Arrive;

        QSpinBox* m_Ssthresh;
        QSpinBox* m_PaquetNombre;
        QComboBox* m_PaquetType;

        QPushButton* m_Valider;
        QMessageBox* m_VerifConfig;

        QPushButton* m_ConfigSimple;
        QPushButton* m_ConfigMaison;
        QPushButton* m_ConfigPme;
        QPushButton* m_ConfigEntreprise;
        QMessageBox* m_VerifReseau;

    public :
        // Constructeur
        ChoixReseau();

        // Destructeur
        ~ChoixReseau();

        // Méthode
        void analyseConfig();

    private slots :
        // Méthodes Slots
        void selectConfigSimple();
        void selectConfigMaison();
        void selectConfigPme();
        void selectConfigEntreprise();

        void verifConfigMessage();

};

#endif // CHOIXRESEAU_H
