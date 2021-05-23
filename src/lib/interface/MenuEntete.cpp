#include "MenuEntete.hpp"

MenuEntete::MenuEntete() : QHBoxLayout()
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

    m_Barre = new QMenuBar();
    m_Fichier = new QMenu("Fichier");
    m_Barre->setStyleSheet("background-color: rgba(35, 39, 42, 255); color: White;");
    m_Barre->setMinimumWidth(1920);
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

    connect(m_Charger,SIGNAL(triggered()),this,SLOT(charger()));
    connect(m_Sauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarder()));
    connect(m_ExporterGraphe,SIGNAL(triggered()),this,SLOT(exporterGraphe()));
    connect(m_Quitter,SIGNAL(triggered()),this,SLOT(quitter()));

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

    m_ModeActuel = Attente;

    // Boutons du QHBoxLayout
    m_ChangerMode = new QPushButton();
    m_ChangerMode->setStyleSheet(s);
    m_ChangerMode->setMaximumHeight(50);
    m_ChangerMode->setMaximumWidth(50);
    m_ChangerMode->setIcon(QIcon("../src/lib/interface/ressources/Play.png"));
    m_ChangerMode->setIconSize(QSize(20,20));
    m_Hlayout->addWidget(m_ChangerMode);

    connect(m_ChangerMode,SIGNAL(clicked()),this, SLOT(changerMode()));

    m_Stop = new QPushButton();
    m_Stop->setStyleSheet(s);
    m_Stop->setMaximumHeight(50);
    m_Stop->setMaximumWidth(50);
    m_Stop->setIcon(QIcon("../src/lib/interface/ressources/Stop.png"));
    m_Stop->setIconSize(QSize(20,20));
    m_Hlayout->addWidget(m_Stop);

    connect(m_Stop,SIGNAL(clicked()),this, SLOT(stop()));

    m_Minuteur = new QTimer();
    connect(m_Minuteur, SIGNAL(timeout()), this, SLOT(rafraichir()));

    m_Montre = new QLabel("00:00:00");
    m_Montre->setMargin(5);
    m_Montre->setStyleSheet("background-color: rgba(64, 68, 75, 255); border-radius: 5px; color: White; font: bold;");
    m_Hlayout->addWidget(m_Montre);

    m_Hlayout->addSpacerItem(item);

    m_Tuto = new QPushButton();
    m_Tuto->setStyleSheet("QPushButton {background-color: rgba(64, 68, 75, 255);"
                          "border-radius: 25px;"
                          "border-width: 10px;"
                          "padding: 15px;}"
                          "QPushButton:hover {background-color: rgba(74, 78, 85, 255);}"
                          "QPushButton:pressed {background-color: rgba(54, 58, 65, 255);}");
    m_Tuto->setMaximumHeight(50);
    m_Tuto->setMaximumWidth(50);
    m_Tuto->setIcon(QIcon("../src/lib/interface/ressources/Tuto.png"));
    m_Tuto->setIconSize(QSize(20,20));
    m_Hlayout->addWidget(m_Tuto);

    connect(m_Tuto,SIGNAL(clicked()),this, SLOT(afficheTuto()));

    //Attribution du QVBoxLayout comme celui de menuentete
    addLayout(m_Vlayout);

}

// Destructeur //
MenuEntete::~MenuEntete() {

}

void MenuEntete::activeExporter(bool m_export) {
    if (m_export)
        m_ExporterGraphe->setDisabled(false);
    else
        m_ExporterGraphe->setDisabled(true);
}

void MenuEntete::charger() {

    QMessageBox messageCharge;
    messageCharge.setText("Souhaitez-vous sauvegarder la configuration actuelle ?");
    messageCharge.addButton(QMessageBox::Yes);
    messageCharge.addButton(QMessageBox::No);
    messageCharge.addButton(QMessageBox::Cancel);
    messageCharge.setDefaultButton(QMessageBox::Cancel);
    int launch = messageCharge.exec();
    if (launch == QMessageBox::Yes) {
        sauvegarder();
    }
    if (launch == QMessageBox::Yes || launch == QMessageBox::No) {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFile);
        QString file_name = "";
        file_name = dialog.getOpenFileName(qobject_cast<QWidget*>(this), tr("Choisissez le fichier a charger"), "../src/include/configReseau", "JSON File(*.json)");
        if (file_name != "") {
            //chargement du reseau
            std::unique_ptr<ReseauGraphe> res;
            chargerConfig(file_name.toUtf8().constData(), res, Contexte::GetInstance().getConfig());
            Contexte::GetInstance().setReseau(res);
            Contexte::GetInstance().charger();
            QMessageBox::information(qobject_cast<QWidget*>(this), "Fichier selectionne", file_name);
        }
    }
}

void MenuEntete::sauvegarder() {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("*.json"));
    QString file_name = "";
    file_name = dialog.getSaveFileName(qobject_cast<QWidget*>(this), tr("Choisissez l'emplacement de sauvegarde"), "../src/include/configReseau", "JSON File(*.json)");
    if (file_name != "") {
        //sauvegarde du réseau
        sauvegarderConfig(file_name.toUtf8().constData(), Contexte::GetInstance().getReseau()->getNom(), Contexte::GetInstance().getConfig());
        QMessageBox::information(qobject_cast<QWidget*>(this), "Fichier selectionne", file_name);
    }
}

void MenuEntete::exporterGraphe() {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("*.png"));
    QString file_name = dialog.getSaveFileName(qobject_cast<QWidget*>(this), tr("Choisissez l'emplacement de sauvegarde"), "../src/include/configReseau", "PNG File(*.png)");
    if (file_name != "") {
        //sauvegarde de l'image
        Contexte::GetInstance().exporterGraphe(file_name);
        QMessageBox::information(qobject_cast<QWidget*>(this), "Fichier selectionne", file_name);
    }
}

void MenuEntete::quitter() {
    QMessageBox messageQuitter;
    messageQuitter.setText("Souhaitez-vous vraiment quitter ?");
    messageQuitter.addButton(QMessageBox::Yes);
    messageQuitter.addButton(QMessageBox::No);
    messageQuitter.setDefaultButton(QMessageBox::No);
    int launch = messageQuitter.exec();
    if(launch == QMessageBox::Yes) {
        qApp->quit();
    }
}

void MenuEntete::rafraichir() {
    Contexte::GetInstance().getTemps() += 500;
    int temp = Contexte::GetInstance().getTemps();
    //3600000 milliseconds in an hour
    long hr = temp / 3600000;
    temp = temp - 3600000 * hr;
    //60000 milliseconds in a minute
    long min = temp / 60000;
    temp = temp - 60000 * min;

    //1000 milliseconds in a second
    long sec = temp / 1000;
    Contexte::GetInstance().rafraichir();
    m_Montre->setText(QStringLiteral("%1").arg(hr, 2, 10, QLatin1Char('0')) + ":" +
                      QStringLiteral("%1").arg(min, 2, 10, QLatin1Char('0')) + ":" +
                      QStringLiteral("%1").arg(sec, 2, 10, QLatin1Char('0')));
}

void MenuEntete::stop() {
    Contexte::GetInstance().stopSimulation();
    m_ChangerMode->setIcon(QIcon("../src/lib/interface/ressources/Play.png"));
    m_ModeActuel = Attente;
    m_Minuteur->stop();
    activeExporter(true);
}

void MenuEntete::changerMode(){
    if(m_ModeActuel == Attente || m_ModeActuel == Pause) {
        if (m_ModeActuel == Attente) {
            m_Montre->setText("00:00:00");
            Contexte::GetInstance().getTemps() = 0;
            Contexte::GetInstance().executerSimulation();
        }
        m_ChangerMode->setIcon(QIcon("../src/lib/interface/ressources/Pause.png"));
        m_ModeActuel = Lecture;
        m_Minuteur->start(500);
        activeExporter(false);
    }
    else if(m_ModeActuel == Lecture) {
        m_ChangerMode->setIcon(QIcon("../src/lib/interface/ressources/Play.png"));
        m_ModeActuel = Pause;
        int remaining = m_Minuteur->remainingTime();
        m_Minuteur->stop();
        m_Minuteur->setInterval(remaining);
        activeExporter(true);
    }
}

void MenuEntete::afficheTuto() {
    QWidget *wdg = new QWidget;
    QGridLayout* lyt = new QGridLayout();
    wdg->setLayout(lyt);
    QLabel* lbl = new QLabel();
    lbl->setPixmap(QPixmap("../src/lib/interface/ressources/Reseau4_Rectangle.png"));
    lyt->addWidget(lbl);
    wdg->show();
}
