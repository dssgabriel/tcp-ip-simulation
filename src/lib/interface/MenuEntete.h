#ifndef MENUENTETE_H
#define MENUENTETE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MenuEntete : public QHBoxLayout
{
Q_OBJECT
    private:
        // Attributs
        QMenuBar* m_Barre;
        QMenu* m_Fichier;

        QAction* m_Charger;
        QAction* m_Sauvegarder;
        QAction* m_ExporterGraphe;
        QAction* m_Quitter;

        QPushButton* m_ChangerMode;
        QPushButton* m_Stop;
        QPushButton* m_Tuto;

        QTimer* m_Minuteur;
        QLabel* m_Montre;

        enum mode { Attente, Lecture, Pause };
        mode m_ModeActuel;

    public:
        // Constructeur
        MenuEntete();

        // Destructeur
        ~MenuEntete();

        /*// Méthode
        void activeExporter(bool m_export);

    private slots :
        // Méthodes Slots
        void charger();
        void sauvegarder();
        void exporterGraphe();
        void quitter();

        void rafraichir();
        void stop();
        void changerMode();
        void afficheTuto();*/

};

#endif // MENUENTETE_H
