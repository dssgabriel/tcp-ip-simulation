/**
 * @file        AffichageReseau.hpp
 * @brief       Déclaration de la classe AffichageReseau.
 * 
 * @author      Johann RAMANANDRAISIORY 
 * @date        2021
 **/

#ifndef AFFICHAGERESEAU_H
#define AFFICHAGERESEAU_H

#include "Contexte.hpp"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QtCharts>
using namespace QtCharts;

class AffichageReseau : public QHBoxLayout
{
Q_OBJECT
    private:
        // Attributs
        AffichageReseau();

        QPushButton* m_Image;

        QChartView* m_Vue;
        QChart* m_Graphique;

        std::vector<QLineSeries*> m_Lignes;
        QHBoxLayout* m_Layout;

    public:
        // Singleton
        static AffichageReseau& GetInstance() {
            static AffichageReseau singleton;
            return singleton;
        }

        // Méthodes de copie
        AffichageReseau(AffichageReseau&) = delete;
        void operator=(AffichageReseau&) = delete;

        // Destructeur
        ~AffichageReseau();

        // Methodes
        void configSimple();
        void configMaison();
        void configPme();
        void configEntreprise();

        void initialiserGraphe();
        void rafraichirGraphe();
        void sauvegarderGraphe(const QString& nomFichier);

    private slots :
        // Méthode Slots
        void informationsReseau();

};

#endif // AFFICHAGERESEAU_H
