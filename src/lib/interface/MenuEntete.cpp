#include "MenuEntete.h"

MenuEntete::MenuEntete() : QHBoxLayout()
{

    // Definition de la StyleSheet pour les widgets(fond degrade orange vers rose, texte blanc de taille 20 pixel, bordure arrondie etc...)
    QString s("QPushButton {background-color: rgba(50, 50, 50, 255);"
               "font: bold;"
               "border-radius: 5px;"
               "color: White;"
               "border-width: 10px;"
               "padding: 15px;}"
               "QPushButton:hover {background-color: rgba(70, 70, 70, 255);}"
               "QPushButton:pressed {background-color: rgba(30, 30, 30, 255);}");

    m_Barre = new QMenuBar();
    m_Fichier = new QMenu("Fichier");
    m_Barre->setStyleSheet("background-color: rgba(80, 80, 80, 255); color: White;");
    m_Barre->setMaximumHeight(30);
    m_Barre->addMenu(m_Fichier);
    setMenuBar(m_Barre);

    // QActions
    m_Charger = new QAction("Charger...");
    m_Sauvegarder = new QAction("Sauvegarder...");
    m_ExporterGraphe = new QAction("Exporter Graphe...");
    m_ExporterGraphe->setDisabled(true);
    m_Quitter = new QAction("Quitter");

    m_Fichier->addAction(m_Charger);
    m_Fichier->addAction(m_Sauvegarder);
    m_Fichier->addAction(m_ExporterGraphe);
    m_Fichier->addAction(m_Quitter);

    QVBoxLayout* m_Vlayout = new QVBoxLayout();

    // Espace permettant d'éviter que les widgets se superposent avec la Barre de Menu
    QSpacerItem *menubarspace = new QSpacerItem(1,17, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_Vlayout->addSpacerItem(menubarspace);

    // Layout contenant les boutons
    QHBoxLayout* m_Hlayout = new QHBoxLayout();
    m_Vlayout->addLayout(m_Hlayout);

    // Espace permettant de centrer les boutons play/pause et le label m_Montre
    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_Hlayout->addSpacerItem(item);

    // Boutons du QHBoxLayout
    m_ChangerMode = new QPushButton("Play");
    m_ChangerMode->setStyleSheet(s);
    m_Hlayout->addWidget(m_ChangerMode);

    m_Stop = new QPushButton("Stop");
    m_Stop->setStyleSheet(s);
    m_Hlayout->addWidget(m_Stop);

    m_Montre = new QLabel("00:00:00");
    m_Montre->setStyleSheet("background-color: rgba(50, 50, 50, 255); border-radius: 5px; color: White; font: bold;");
    m_Hlayout->addWidget(m_Montre);

    m_Hlayout->addSpacerItem(item);

    m_Tuto = new QPushButton("Tuto");
    m_Tuto->setStyleSheet(s);
    m_Hlayout->addWidget(m_Tuto);

    //Attribution du QVBoxLayout comme celui de menuentete
    addLayout(m_Vlayout);

}

// Destructeur //
MenuEntete::~MenuEntete() {

}
