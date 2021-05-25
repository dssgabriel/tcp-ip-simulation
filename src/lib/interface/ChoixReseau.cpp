/**
 * @file        ChoixReseau.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe ChoixReseau.
 *
 * @author      Jean-Christophe CHALAUD
 * @author      Raphael LIN
 * @date        2021
 **/

#include "ChoixReseau.hpp"

 /**
  * @brief Constructeur de la classe ChoixReseau.
  *
  * Le constructeur contient :
  * Un ensemble de parametres necesaires au fonctionnement de la simulation(machine de depart, machine d'arrivee,
  * taille de la fenetre, nombre de paquet, type de paquet).
  * Un bouton valider qui va recuperer toutes les informations selectionees pour les envoiyer aux differents modules qui
  * appelent la fonction verifConfigMessage().
  * Les boutons permetant de choisir le reseau voulu qui vont appeler respectivement les fonctions selectConfigSimple(),
  * sectConfigMaison(), selectConfigPme(), selectConfigEntreprise().
  **/
ChoixReseau::ChoixReseau() : QVBoxLayout()
{

    // Definition de la StyleSheet pour les widgets(fond degrade orange vers rose, texte blanc de taille 20 pixel, bordure arrondie etc...)
    QString s("QPushButton {background-color: rgba(64, 68, 75, 255);"
               "font: bold;"
               "border-radius: 5px;"
               "color: White;"
               "border-width: 10px;"
               "padding: 15px;}"
               "QPushButton:hover {background-color: rgba(74, 78, 85, 255);}"
               "QPushButton:pressed {background-color: rgba(54, 58, 65, 255);}");


    QVBoxLayout* m_Vlayout = new QVBoxLayout();

    // Ajout d'une frame dans le layout m_Vlayout
    QFrame* frame = new QFrame();
    m_Vlayout->addWidget(frame);
    frame->setStyleSheet("background-color: rgba(64, 68, 75, 255); border-radius: 5px;");

    // Ajout d'un layout dans la frame
    QVBoxLayout* Framelayout = new QVBoxLayout();
    frame->setLayout(Framelayout);

    //les QComboBox des machines d'arriver et de depart

    QLabel* m_LabelDepart = new QLabel("Machine de depart");
    m_LabelDepart->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgba(142, 146, 151, 255); font: bold;");
    m_Depart = new QComboBox();
    m_Depart->setStyleSheet("background-color: rgba(44, 47, 51, 255); color : white;");
    Framelayout->addWidget(m_LabelDepart);
    Framelayout->addWidget(m_Depart);

    QLabel* m_LabelArriver = new QLabel("Machine d'arrivee");
    m_LabelArriver->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgba(142, 146, 151, 255); font: bold;");
    m_Arrive = new QComboBox();
    m_Arrive->setStyleSheet("background-color: rgba(44, 47, 51, 255); color : white;");
    Framelayout->addWidget(m_LabelArriver);
    Framelayout->addWidget(m_Arrive);

    //les QSpinBox du QVBoxLayout

    QLabel* m_LabelSsthresh = new QLabel("Taille de la fenetre");
    m_LabelSsthresh->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgba(142, 146, 151, 255); font: bold;");
    Framelayout->addWidget(m_LabelSsthresh);
    m_Ssthresh = new QSpinBox;
    m_Ssthresh->setRange(128, 255);
    m_Ssthresh->setStyleSheet("background-color: rgba(44, 47, 51, 255); color : white;");
    Framelayout->addWidget(m_Ssthresh);

    QLabel* m_LabelPaquetNombre = new QLabel("Nombre de paquets");
    m_LabelPaquetNombre->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgba(142, 146, 151, 255); font: bold;");
    Framelayout->addWidget(m_LabelPaquetNombre);
    m_PaquetNombre = new QSpinBox;
    m_PaquetNombre->setRange(10, 2000);
    m_PaquetNombre->setStyleSheet("background-color: rgba(44, 47, 51, 255); color : white;");
    Framelayout->addWidget(m_PaquetNombre);

    //QComboBox types paquet

    QLabel* m_LabelPaquetTypes = new QLabel("Type de paquet");
    m_LabelPaquetTypes->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: rgba(142, 146, 151, 255); font: bold;");
    m_PaquetType = new QComboBox();
    m_PaquetType->setStyleSheet("background-color: rgba(44, 47, 51, 255); color : white;");
    m_PaquetType->addItem("FTP");
    m_PaquetType->addItem("HTTP");
    m_PaquetType->addItem("SMTP");
    m_PaquetType->addItem("VTP");
    Framelayout->addWidget(m_LabelPaquetTypes);
    Framelayout->addWidget(m_PaquetType);

    //Label vide pour faire de l'espace au dessus du bouton
    QLabel* empty = new QLabel();
    empty->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    empty->setMinimumHeight(10);
    Framelayout->addWidget(empty);

    //boutton du QVBoxLayout
    m_Valider = new QPushButton(" Valider ");
    m_Valider->setStyleSheet("QPushButton {background-color: rgba(88, 101, 242, 255);"
                             "font: bold;"
                             "border-radius: 5px;"
                             "color: White;"
                             "border-width: 10px;"
                             "padding: 15px;}"
                             "QPushButton:hover {background-color: rgba(68, 81, 222, 255);}"
                             "QPushButton:pressed {background-color: rgba(48, 61, 202, 255);}");
    Framelayout->addWidget(m_Valider);


    m_ConfigSimple = new QPushButton();
    m_ConfigSimple->setStyleSheet(s);
    m_ConfigSimple->setMaximumHeight(100);
    m_ConfigSimple->setMaximumWidth(260);
    m_ConfigSimple->setIcon(QIcon("../src/lib/interface/ressources/Reseau1.png"));
    m_ConfigSimple->setIconSize(QSize(250,250));
    m_Vlayout->addWidget(m_ConfigSimple);

    m_ConfigMaison = new QPushButton();
    m_ConfigMaison->setStyleSheet(s);
    m_ConfigMaison->setMaximumHeight(100);
    m_ConfigMaison->setMaximumWidth(260);
    m_ConfigMaison->setIcon(QIcon("../src/lib/interface/ressources/Reseau2.png"));
    m_ConfigMaison->setIconSize(QSize(250,250));
    m_Vlayout->addWidget(m_ConfigMaison);

    m_ConfigPme = new QPushButton();
    m_ConfigPme->setStyleSheet(s);
    m_ConfigPme->setMaximumHeight(100);
    m_ConfigPme->setMaximumWidth(260);
    m_ConfigPme->setIcon(QIcon("../src/lib/interface/ressources/Reseau3.png"));
    m_ConfigPme->setIconSize(QSize(250,250));
    m_Vlayout->addWidget(m_ConfigPme);

    m_ConfigEntreprise = new QPushButton();
    m_ConfigEntreprise->setStyleSheet(s);
    m_ConfigEntreprise->setMaximumHeight(100);
    m_ConfigEntreprise->setMaximumWidth(260);
    m_ConfigEntreprise->setIcon(QIcon("../src/lib/interface/ressources/Reseau4.png"));
    m_ConfigEntreprise->setIconSize(QSize(250,250));
    m_Vlayout->addWidget(m_ConfigEntreprise);

    //Attribution du QVBoxLayout comme celui de menuentete
    addLayout(m_Vlayout);

    //connection des differents boutons de la calsse

    connect(m_Valider,SIGNAL(clicked()),this, SLOT(verifConfigMessage()));
    connect(m_ConfigSimple,SIGNAL(clicked()),this, SLOT(selectConfigSimple()));
    connect(m_ConfigMaison,SIGNAL(clicked()),this, SLOT(selectConfigMaison()));
    connect(m_ConfigPme,SIGNAL(clicked()),this, SLOT(selectConfigPme()));
    connect(m_ConfigEntreprise,SIGNAL(clicked()),this, SLOT(selectConfigEntreprise()));

    analyseConfig();
}

/**
  * @brief Destructeur de la classe ChoixReseau.
  *
  * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
  *
  **/

ChoixReseau::~ChoixReseau()
{

}

/**
  * @brief Permet d'envoyer toutes les informations concernant le reseau.
  *
  * @return void
  **/

void ChoixReseau::verifConfigMessage(){

    if (m_Depart->currentText() == m_Arrive->currentText()) {
        QMessageBox::information(qobject_cast<QWidget*>(this), "Erreur", "Veuillez choisir une machine de depart et une machine d'arrivee differentes");
        return;
    }
    QMessageBox m_VerifConfig;
    m_VerifConfig.setText("Voulez-vous vraiment valider vos choix ?");
    m_VerifConfig.setStandardButtons(QMessageBox::Yes);
    m_VerifConfig.addButton(QMessageBox::No);
    m_VerifConfig.setDefaultButton(QMessageBox::No);
    if(m_VerifConfig.exec() == QMessageBox::Yes){
        QString m_Tempo1,m_Tempo2;
        m_Tempo1 = m_Depart->currentText();
        m_Tempo2 = m_Arrive->currentText();

        int m_Indice = m_PaquetType->currentIndex();

        auto vector = Contexte::GetInstance().getReseau()->getMachines();
        for(std::size_t i =0; i < vector.size(); i++){
            QString m_StringToQstring;
            if(m_StringToQstring.fromStdString(vector[i]->getNom()) == m_Tempo1){
                Contexte::GetInstance().getConfig().m_Source = vector[i]->getIp();
            }
            if(m_StringToQstring.fromStdString(vector[i]->getNom()) == m_Tempo2){
                Contexte::GetInstance().getConfig().m_Destination = vector[i]->getIp();
            }
        }
        Contexte::GetInstance().getConfig().m_Ssthresh = m_Ssthresh->value() ;
        Contexte::GetInstance().getConfig().m_NbPaquet = m_PaquetNombre->value();
        if(m_Indice == 0){
            Contexte::GetInstance().getConfig().m_TypeFichier = FTP;
        }
        else if(m_Indice == 1){
            Contexte::GetInstance().getConfig().m_TypeFichier = HTTP;
        }
        else if(m_Indice == 2){
            Contexte::GetInstance().getConfig().m_TypeFichier = SMTP;
        }
        else if(m_Indice == 3){
            Contexte::GetInstance().getConfig().m_TypeFichier = VTP;
        }
        QDialog *wdg = new QDialog;
        wdg->setWindowFlag(Qt::WindowStaysOnTopHint, true);
        wdg->setWindowFlag(Qt::FramelessWindowHint, true);
        wdg->setWindowFlag(Qt::NoDropShadowWindowHint, true);
        wdg->setModal(true);
        wdg->setStyleSheet("background-color: rgba(44, 47, 51, 255);");
        QGridLayout* lyt = new QGridLayout();
        lyt->setMargin(0);
        lyt->setSpacing(0);
        wdg->setLayout(lyt);
        QLabel* lbl = new QLabel("Chargement...");
        lbl->setMinimumSize(150,70);
        lbl->setStyleSheet("background-color: rgba(88, 101, 242, 255); font: bold; border-radius: 5px; color: White;");
        lbl->setAlignment(Qt::AlignCenter);
        lyt->addWidget(lbl);
        wdg->show();
        QApplication::processEvents();
        Contexte::GetInstance().chargementSimulation();
        wdg->close();
    }
}

 /**
  * @brief Permet de selectionner le reseau simple.
  *
  *
  * @return void
  *
  **/

void ChoixReseau::selectConfigSimple(){
    QMessageBox m_Simple;
    m_Simple.setText("Choix du Reseau Simple");
    m_Simple.setStandardButtons(QMessageBox::Yes);
    m_Simple.addButton(QMessageBox::No);
    m_Simple.setDefaultButton(QMessageBox::No);
    if(m_Simple.exec() == QMessageBox::Yes){
        Contexte::GetInstance().chargerConfig(1);
    }
    else{
        QMessageBox m_Simple;
        m_Simple.setText("Veuillez choisir un reseau");
        m_Simple.exec();
    }
}

 /**
  * @brief Permet de selectionner le reseau maison.
  *
  *
  * @return void
  **/

void ChoixReseau::selectConfigMaison(){

    QMessageBox m_Maison;
    m_Maison.setText("Choix du Reseau Maison");
    m_Maison.setStandardButtons(QMessageBox::Yes);
    m_Maison.addButton(QMessageBox::No);
    m_Maison.setDefaultButton(QMessageBox::No);
    if(m_Maison.exec() == QMessageBox::Yes){
        Contexte::GetInstance().chargerConfig(2);
    }
    else{
        QMessageBox m_Maison;
        m_Maison.setText("Veuillez choisir un reseau");
        m_Maison.exec();
    }

}

 /**
  * @brief Permet de selectionner le reseau Pme.
  *
  *
  * @return void
  **/

void ChoixReseau::selectConfigPme(){

    QMessageBox m_Pme;
    m_Pme.setText("Choix du Reseau Pme");
    m_Pme.setStandardButtons(QMessageBox::Yes);
    m_Pme.addButton(QMessageBox::No);
    m_Pme.setDefaultButton(QMessageBox::No);
    if(m_Pme.exec() == QMessageBox::Yes){
        Contexte::GetInstance().chargerConfig(3);
    }
    else{
        QMessageBox m_Pme;
        m_Pme.setText("Veuillez choisir un reseau");
        m_Pme.exec();
    }

}

 /**
  * @brief Permet de selectionner le reseau entreprise.
  *
  *
  * @return void
  **/

void ChoixReseau::selectConfigEntreprise(){

    QMessageBox m_Entreprise;
    m_Entreprise.setText("Choix du Reseau Entreprise");
    m_Entreprise.setStandardButtons(QMessageBox::Yes);
    m_Entreprise.addButton(QMessageBox::No);
    m_Entreprise.setDefaultButton(QMessageBox::No);
    if(m_Entreprise.exec() == QMessageBox::Yes){
        Contexte::GetInstance().chargerConfig(4);
    }
    else{
        QMessageBox m_Entreprise;
        m_Entreprise.setText("Veuillez choisir un reseau");
        m_Entreprise.exec();
    }

}

 /**
  * @brief Permet d'afficher les differentes machines possibles dans les QComboBox.
  *
  * Permet aussi de mettre les valeurs de la configuration choisie dans les combobox et les spinbox.
  *
  * @return void
  **/

void ChoixReseau::analyseConfig(){
    m_Depart->clear();
    m_Arrive->clear();

    auto vector = Contexte::GetInstance().getReseau()->getMachines();
    m_Depart->setStyleSheet("background-color: rgba(44, 47, 51, 255); color : white;");

    for(std::size_t i =0; i < vector.size(); i++){
        QString m_StringToQstring;
        if(vector[i]->getNom()[0] == 'O'){
            m_Depart->addItem(m_StringToQstring.fromStdString(vector[i]->getNom()));
            m_Arrive->addItem(m_StringToQstring.fromStdString(vector[i]->getNom()));
        }
    }

    int j = 0;
    for(std::size_t i =0; i < vector.size(); i++){
        if(vector[i]->getNom()[0] == 'O'){
            if(Contexte::GetInstance().getConfig().m_Source == vector[i]->getIp()){
                m_Depart->setCurrentIndex(j);
            }
            if(Contexte::GetInstance().getConfig().m_Destination == vector[i]->getIp()){
                m_Arrive->setCurrentIndex(j);
            }
            j++;
        }
    }

    m_Ssthresh->setValue(Contexte::GetInstance().getConfig().m_Ssthresh);
    m_PaquetNombre->setValue(Contexte::GetInstance().getConfig().m_NbPaquet);

    if(Contexte::GetInstance().getConfig().m_TypeFichier == FTP){
        m_PaquetType->setCurrentIndex(0);
    }
    else if(Contexte::GetInstance().getConfig().m_TypeFichier == HTTP){
        m_PaquetType->setCurrentIndex(1);
    }
    else if(Contexte::GetInstance().getConfig().m_TypeFichier == SMTP){
        m_PaquetType->setCurrentIndex(2);
    }
    else if(Contexte::GetInstance().getConfig().m_TypeFichier == VTP){
        m_PaquetType->setCurrentIndex(3);
    }
}


