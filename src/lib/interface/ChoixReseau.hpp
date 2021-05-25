/**
 * @file ChoixReseau.hpp
 * @author Jean-Christophe
 * @brief Vous trouverez ici la declaration de la classe ChoixReseau
 * @date 2021
 * 
 */
#ifndef CHOIXRESEAU_H
#define CHOIXRESEAU_H

#include "Contexte.hpp"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QFrame>

class ChoixReseau : public QVBoxLayout
{
Q_OBJECT
    private :
        // Attributs
        ChoixReseau();

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
        // Singleton
        static ChoixReseau& GetInstance() {
            static ChoixReseau singleton;
            return singleton;
        }

        // Méthodes de copie
        ChoixReseau(ChoixReseau&) = delete;
        void operator=(ChoixReseau&) = delete;

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
