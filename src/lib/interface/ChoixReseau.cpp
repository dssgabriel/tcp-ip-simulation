#include "ChoixReseau.h"

ChoixReseau::ChoixReseau() : QVBoxLayout()
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


    QVBoxLayout* m_Vlayout = new QVBoxLayout();


    //les QComboBox des machines d'arriver et de depart

    QLabel* m_LabelDepart = new QLabel("Machine de depart");
    m_LabelDepart->setStyleSheet("color : white;");
    QComboBox* m_Depart = new QComboBox();
    for(int i = 0; i<15; i++){
        m_Depart->addItem("Machine "+ QString::number(i));
    }
    m_Vlayout->addWidget(m_LabelDepart);
    m_Vlayout->addWidget(m_Depart);

    QLabel* m_LabelArriver = new QLabel("Machine d'arriver");
    m_LabelArriver->setStyleSheet("color : white;");
    QComboBox* m_Arrive = new QComboBox();
    for(int i = 0; i<15; i++){
        m_Arrive->addItem("Machine "+ QString::number(i));
    }
    m_Vlayout->addWidget(m_LabelArriver);
    m_Vlayout->addWidget(m_Arrive);



    //les QSpinBox du QVBoxLayout

    QLabel* m_LabelSsthresh = new QLabel("Entrez la taille de la fenetre");
    m_LabelSsthresh->setStyleSheet("color : white;");
    m_Vlayout->addWidget(m_LabelSsthresh);
    QSpinBox* m_Ssthresh = new QSpinBox;
    m_Ssthresh->setRange(128,256);
    m_Ssthresh->setMinimum(128);
    m_Ssthresh->setMaximum(256);
    m_Ssthresh->setStyleSheet("color : white;");
    m_Vlayout->addWidget(m_Ssthresh);

    QLabel* m_LabelPaquetNombre = new QLabel("Entrez le nombre de paquet a envoyer");
    m_LabelPaquetNombre->setStyleSheet("color : white;");
    m_Vlayout->addWidget(m_LabelPaquetNombre);
    QSpinBox* m_PaquetNombre = new QSpinBox;
    m_PaquetNombre->setRange(1,65536);
    m_PaquetNombre->setMaximum(65536);
    m_PaquetNombre->setStyleSheet("color : white;");
    m_Vlayout->addWidget(m_PaquetNombre);

    //QComboBox types paquet

    QLabel* m_LabelPaquetTypes = new QLabel("types de paquets a envoyer");
    m_LabelPaquetTypes->setStyleSheet("color : white;");
    QComboBox* m_PaquetType = new QComboBox();
    m_PaquetType->addItem("FTP");
    m_PaquetType->addItem("HTTP");
    m_PaquetType->addItem("SMTP");
    m_PaquetType->addItem("VTP");
    m_Vlayout->addWidget(m_LabelPaquetTypes);
    m_Vlayout->addWidget(m_PaquetType);

    QHBoxLayout* m_Hlayout = new QHBoxLayout();
    m_Vlayout->addLayout(m_Hlayout);

    //boutton du QVBoxLayout

    m_Valider = new QPushButton();
    m_Valider->setStyleSheet("QPushButton {background-color: rgba(180, 180, 180, 255);"
                             "border-radius: 28px;"
                             "border-width: 5px;"
                             "padding: 15px;}"
                             "QPushButton:hover {background-color: white;}"
                             "QPushButton:pressed {background-color: rgba(180, 180, 180, 255);}");
    m_Valider->setMaximumHeight(58);
    m_Valider->setMaximumWidth(58);
    m_Valider->setIcon(QIcon("../src/lib/interface/ressources/Valider.png"));
    m_Valider->setIconSize(QSize(56,56));
    m_Hlayout->setAlignment(Qt::AlignCenter);
    m_Hlayout->addWidget(m_Valider);


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


}

ChoixReseau::~ChoixReseau()
{

}

void ChoixReseau::verifConfigMessage(){

    QMessageBox m_VerifConfig;
    m_VerifConfig.setText("Etes vous sure des choix selectioner ");
    m_VerifConfig.setStandardButtons(QMessageBox::Yes);
    m_VerifConfig.addButton(QMessageBox::No);
    m_VerifConfig.setDefaultButton(QMessageBox::No);
    if(m_VerifConfig.exec() == QMessageBox::Yes){
        //appel de contexte pour faire le lien avec le restes
        //du projet
    }
    else{
       QMessageBox m_Information;
       m_Information.setText("veuillez rentrer les parametres desirer");
       m_Information.exec();
    }
}

void ChoixReseau::selectConfigSimple(){

    QMessageBox msgbox;
    msgbox.setText("configuration simple");
    msgbox.exec();
}

void ChoixReseau::selectConfigMaison(){

    QMessageBox msgbox;
    msgbox.setText("configuration maison");
    msgbox.exec();

}

void ChoixReseau::selectConfigPme(){

    QMessageBox msgbox;
    msgbox.setText("configuration pme");
    msgbox.exec();

}

void ChoixReseau::selectConfigEntreprise(){

    QMessageBox msgbox;
    msgbox.setText("configuration entreprise");
    msgbox.exec();

}

void analyseConfig(){
    
}


