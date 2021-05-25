/**
 * @file        AffichageReseau.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe AffichageReseau.
 *
 * @author      Johann RAMANANDRAITSIORY
 * @author      Raphael LIN
 * @date        2021
 **/

#include "AffichageReseau.hpp"

 /**
  * @brief Constructeur de la classe AffichageReseau.
  *
  * Le constructeur contient :
  * Le bouton affichant le réseau de configuration (ici on affiche le réseau Simple).
  * Le graphique composé des légendes(titre + axes) et des couleurs qui le représentent.
  * De plus le bouton appelle la fonction informationsReseau() si l'on clique dessus.
  **/
AffichageReseau::AffichageReseau() : QHBoxLayout()
{
    // Definition de la StyleSheet pour les widgets //
    QString s("QPushButton {background-color: rgba(64, 68, 75, 255);"
               "font: bold;"
               "border-radius: 5px;"
               "color: White;"
               "border-width: 10px;"
               "padding: 15px;}"
               "QPushButton:hover {background-color: rgba(74, 78, 85, 255);}"
               "QPushButton:pressed {background-color: rgba(54, 58, 65, 255);}");

    // Création du bouton principale affichant le réseau //
    m_Image = new QPushButton("");
    m_Image ->setStyleSheet(s);
    QPixmap pixmap("../src/lib/interface/ressources/Reseau1_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
    m_Image->setMaximumSize(QSize(347, 700));
    m_Image->setIconSize(QSize(347, 550));
    addWidget(m_Image);

    // Connexion bouton & fonction informationReseau() //
    connect(m_Image,SIGNAL(clicked()),this,SLOT(informationsReseau()));

    // Déclaration du Graphique //
    m_Vue = new QChartView();
    m_Vue->setRenderHint(QPainter::Antialiasing);
    m_Vue->setStyleSheet("background-color: rgba(64, 68, 75, 255); border-radius: 5px; font: bold;");
    m_Graphique = m_Vue->chart();
    m_Graphique->setTitle("Controle de Congestion TCP/IP");
    m_Graphique->setTheme(QChart::ChartThemeDark);
    m_Graphique->titleFont().setBold(true);

    // Déclaration des différents modes du contrôle de congestion //
    // a) Slow Start //
    QLineSeries* slow_start = new QLineSeries();
    slow_start->setName("Slow Start");
    m_Lignes.push_back(slow_start);
    m_Graphique->addSeries(slow_start);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[0]->setColor(QColor(255,105,180,255));

    // b) Congestion Avoidance //
    QLineSeries* cong_avoid = new QLineSeries();
    cong_avoid->setName("Congestion Avoidance");
    m_Lignes.push_back(cong_avoid);
    m_Graphique->addSeries(cong_avoid);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[1]->setColor(QColor(Qt::cyan));

    // c) Fast Retransmit //
    QLineSeries* fast_retransmit = new QLineSeries();
    fast_retransmit->setName("Fast Retransmit");
    m_Lignes.push_back(fast_retransmit);
    m_Graphique->addSeries(fast_retransmit);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[2]->setColor(QColor(138,43,226,255));

    // d) Fast Recovery //
    QLineSeries* fast_recovery = new QLineSeries();
    fast_recovery->setName("Fast Recovery");
    m_Lignes.push_back(fast_recovery);
    m_Graphique->addSeries(fast_recovery);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[3]->setColor(QColor(Qt::green));

    addWidget(m_Vue);
}

 /**
  * @brief Destructeur de la classe AffichageReseau.
  *
  * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
  *
  * @return void
  **/
AffichageReseau::~AffichageReseau() {

}

 /**
  * @brief Permet d'afficher le Réseau de configuration Simple.
  *
  * On cherche l'image dans le dossier ressource.
  * Puis on ajoute celle-ci au QPushButton m_Image.
  *
  * @return void
  **/
void AffichageReseau::configSimple()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau1_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);

}

 /**
  * @brief Permet d'afficher le Réseau de configuration Maison.
  *
  * On cherche l'image dans le dossier ressource.
  * Puis on ajoute celle-ci au QPushButton m_Image.
  *
  * @return void
  **/
void AffichageReseau::configMaison()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau2_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
}

 /**
  * @brief Permet d'afficher le Réseau de configuration Pme.
  *
  * On cherche l'image dans le dossier ressource.
  * Puis on ajoute celle-ci au QPushButton m_Image.
  *
  * @return void
  **/
void AffichageReseau::configPme()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau3_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
}

 /**
  * @brief Permet d'afficher le Réseau de configuration Entreprise.
  *
  * On cherche l'image dans le dossier ressource.
  * Puis on ajoute celle-ci au QPushButton m_Image.
  *
  * @return void
  **/
void AffichageReseau::configEntreprise()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau4_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
}

 /**
  * @brief Permet d'initialiser le graphique.
  *
  * On ajoute la légende au deux axes abscisses et ordonnées.
  * Puis on définit la taille des deux axes.
  *
  * @return void
  **/
void AffichageReseau::initialiserGraphe()
{
    // On vide le vector m_Lignes + suppression du graphe dessiner au départ //
    m_Lignes.clear();
    m_Graphique->removeAllSeries();

    // On trouve le maximum de la fenêtre de la simulation
    int max = 0;
    auto vector = Contexte::GetInstance().getTab();
    for(std::size_t it = 0; it < vector->size(); it++){
        if ((*vector)[it].m_ValeurCwnd > max)
            max = (*vector)[it].m_ValeurCwnd;
    }
    max *= 1.3;

    // Déclaration des différents modes du contrôle de congestion //
    // a) Slow Start //
    QLineSeries* slow_start = new QLineSeries();
    slow_start->setName("Slow Start");
    m_Lignes.push_back(slow_start);
    m_Graphique->addSeries(slow_start);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, max);
    m_Lignes[0]->setColor(QColor(255,105,180,255));

    // b) Congestion Avoidance //
    QLineSeries* cong_avoid = new QLineSeries();
    cong_avoid->setName("Congestion Avoidance");
    m_Lignes.push_back(cong_avoid);
    m_Graphique->addSeries(cong_avoid);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, max);
    m_Lignes[1]->setColor(QColor(Qt::cyan));

    // c) Fast Retransmit //
    QLineSeries* fast_retransmit = new QLineSeries();
    fast_retransmit->setName("Fast Retransmit");
    m_Lignes.push_back(fast_retransmit);
    m_Graphique->addSeries(fast_retransmit);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, max);
    m_Lignes[2]->setColor(QColor(138,43,226,255));

    // d) Fast Recovery //
    QLineSeries* fast_recovery = new QLineSeries();
    fast_recovery->setName("Fast Recovery");
    m_Lignes.push_back(fast_recovery);
    m_Graphique->addSeries(fast_recovery);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 100);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, max);
    m_Lignes[3]->setColor(QColor(Qt::green));

    m_Lignes[0]->append(0,0);
}

 /**
  * @brief Permet de tracer et dessiner le graphique du contrôle de congestion.
  *
  * On trace une courbe de couleur définie selon le mode du contrôle de congestion.
  *
  * @return void
  **/

void AffichageReseau::rafraichirGraphe()
{
    // Variable pour le fonctionnement de la fonction //
    int timer_act = Contexte::GetInstance().getTemps() / 200;
    auto vector = Contexte::GetInstance().getTab();

    // Définition des couleurs + formes des QPen pour dessiner le graphique //
    QPen pen1(QColor(255,105,180,255));
    pen1.setWidth(3);
    pen1.setStyle(Qt::DashLine);

    QPen pen2(QColor(Qt::cyan));
    pen2.setWidth(3);
    pen2.setStyle(Qt::DashLine);

    QPen pen3(QColor(138,43,226,255));
    pen3.setWidth(3);
    pen3.setStyle(Qt::DashLine);

    QPen pen4(QColor(Qt::green));
    pen4.setWidth(3);
    pen4.setStyle(Qt::DashLine);

    for(std::size_t i =0; i < vector->size(); i++)
    {
        if(timer_act >= (*vector)[i].m_Temps && timer_act - 1 < (*vector)[i].m_Temps)
        {
            // Le premier point sera toujours dans le mode Slow Start //
            if(i == 0)
            {
                *m_Lignes[0] << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                m_Lignes[0]->setPen(pen1);
                m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);
            }

            // Si le point est dans le même mode que le précédent //
            // On l'ajoute au vecteur m_Lignes respectif //

            else if((*vector)[i].m_Mode == (*vector)[i-1].m_Mode && i != 0)
            {
                if ((*vector)[i].m_Mode == SlowStart)
                {
                    for(std::size_t it1 = m_Lignes.size()-1; it1 >= 0; it1--)
                    {
                        if (m_Lignes[it1]->name() == "Slow Start")
                        {
                            *m_Lignes[it1] << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                            m_Lignes[it1]->setPen(pen1);
                            m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);
                            break;
                        }
                    }
                }

                if ((*vector)[i].m_Mode == CongestionAvoidance)
                {
                    for(std::size_t it2 = m_Lignes.size()-1; it2 >= 0; it2--)
                    {
                        if (m_Lignes[it2]->name() == "Congestion Avoidance")
                        {
                            *m_Lignes[it2] << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                            m_Lignes[it2]->setPen(pen2);
                            m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);
                            break;
                        }
                    }
                }

                if ((*vector)[i].m_Mode == FastRetransmit)
                {
                    for(std::size_t it3 = m_Lignes.size()-1; it3 >= 0; it3--)
                    {
                        if (m_Lignes[it3]->name() == "Fast Retransmit")
                        {
                            *m_Lignes[it3] << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                            m_Lignes[it3]->setPen(pen3);
                            m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);
                            break;
                        }
                    }
                }

                if ((*vector)[i].m_Mode == FastRecovery)
                {
                    for(std::size_t it4 = m_Lignes.size()-1; it4 >= 0; it4--)
                    {
                        if (m_Lignes[it4]->name() == "Fast Recovery")
                        {
                            *m_Lignes[it4] << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                            m_Lignes[it4]->setPen(pen4);
                            m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);
                            break;
                        }
                    }
                }

            }

            // Si le point est dans un autre mode que le précédent //
            // On crée une nouvelle QLineSeries //
            else if ((*vector)[i-1].m_Mode != (*vector)[i].m_Mode && i != 0)
            {
                if ((*vector)[i].m_Mode == SlowStart)
                {
                    QLineSeries* tmp = new QLineSeries();
                    tmp->setName("Slow Start");
                    m_Lignes.push_back(tmp);
                    m_Graphique->addSeries(tmp);
                    m_Graphique->createDefaultAxes();
                    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
                    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
                    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);

                    *m_Lignes[m_Lignes.size()-1] << QPointF((*vector)[i-1].m_Temps, (*vector)[i-1].m_ValeurCwnd) << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                    m_Lignes[m_Lignes.size()-1]->setPen(pen1);
                }

                if ((*vector)[i].m_Mode == CongestionAvoidance)
                {
                    QLineSeries* tmp = new QLineSeries();
                    tmp->setName("Congestion Avoidance");
                    m_Lignes.push_back(tmp);
                    m_Graphique->addSeries(tmp);
                    m_Graphique->createDefaultAxes();
                    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
                    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
                    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);

                    *m_Lignes[m_Lignes.size()-1] << QPointF((*vector)[i-1].m_Temps, (*vector)[i-1].m_ValeurCwnd) << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                    m_Lignes[m_Lignes.size()-1]->setPen(pen2);
                }

                if ((*vector)[i].m_Mode == FastRetransmit)
                {
                    QLineSeries* tmp = new QLineSeries();
                    tmp->setName("Fast Retransmit");
                    m_Lignes.push_back(tmp);
                    m_Graphique->addSeries(tmp);
                    m_Graphique->createDefaultAxes();
                    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
                    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
                    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);

                    *m_Lignes[m_Lignes.size()-1] << QPointF((*vector)[i-1].m_Temps, (*vector)[i-1].m_ValeurCwnd) << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                    m_Lignes[m_Lignes.size()-1]->setPen(pen3);
                }

                if ((*vector)[i].m_Mode == FastRecovery)
                {
                    QLineSeries* tmp = new QLineSeries();
                    tmp->setName("Fast Recovery");
                    m_Lignes.push_back(tmp);
                    m_Graphique->addSeries(tmp);
                    m_Graphique->createDefaultAxes();
                    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en s");
                    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
                    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, (*vector)[i].m_Temps);

                    *m_Lignes[m_Lignes.size()-1] << QPointF((*vector)[i-1].m_Temps, (*vector)[i-1].m_ValeurCwnd) << QPointF((*vector)[i].m_Temps, (*vector)[i].m_ValeurCwnd);
                    m_Lignes[m_Lignes.size()-1]->setPen(pen4);
                }
            }
            // break;
        }
    }
}

 /**
  * @brief Permet de sauvegarder le graphique du contrôle de congestion.
  *
  * Création d'une variable QImage pour transporter le résultat du graphique.
  * Puis on sauvegarde l'image au format PNG.
  *
  * @param const QString& nomFichier souhaité.
  * @return void
  **/
void AffichageReseau::sauvegarderGraphe(const QString& nomFichier)
{
  QPixmap png_graphe = m_Vue->grab();
  QImage image = png_graphe.toImage();
  image.save(nomFichier,"PNG");
}

 /**
  * @brief Permet d'afficher les informations concernant le réseau étudié.
  *
  * Création d'une nouvelle fenêtre pour afficher les informations manquantes
  * à la configuration du réseau.
  * Ajout d'une variable QLabel pour présenter le réseau accompagné du débit.
  * Puis on instancie un QTextEdit pour pouvoir y instaurer les caractéristiques
  * de chaque machine (ip,mac,masque).
  *
  * @return void
  **/
void AffichageReseau::informationsReseau()
{
    QWidget *wdg = new QWidget;
    wdg->setStyleSheet("background-color: rgba(44, 47, 51, 255);");
    QGridLayout* lyt = new QGridLayout();
    wdg->setLayout(lyt);
    QLabel* lbl = new QLabel();

    // Affichage RéseauSimple composé du : //
    // 1) Débit //
    // 2) Informations réseau (Id machine | Ip | MAC | Masque)
    if(Contexte::GetInstance().getReseau()->getNom() == "ReseauSimple")
    {
        lbl->setPixmap(QPixmap("../src/lib/interface/ressources/simple.png"));
        lyt->addWidget(lbl,0,0);
    }

    else if(Contexte::GetInstance().getReseau()->getNom() == "ReseauMaison")
    {
        lbl->setPixmap(QPixmap("../src/lib/interface/ressources/maison.png"));
        lyt->addWidget(lbl,0,0);
    }

    else if(Contexte::GetInstance().getReseau()->getNom() == "ReseauPME")
    {
        lbl->setPixmap(QPixmap("../src/lib/interface/ressources/pme.png"));
        lyt->addWidget(lbl,0,0);
    }

    else if(Contexte::GetInstance().getReseau()->getNom() == "ReseauEntreprise")
    {
        lbl->setPixmap(QPixmap("../src/lib/interface/ressources/entreprise.png"));
        lyt->addWidget(lbl,0,0);
    }

    // QTextEdit pour exposer la fenêtre du texte //
    QTextEdit * m_InfoReseau = new QTextEdit();
    m_InfoReseau->setStyleSheet("background-color: rgba(64, 68, 75, 255); font: bold; border-radius: 5px;");
    m_InfoReseau->setTextColor(QColor(88, 101, 242, 255));
    m_InfoReseau->setTextColor(QColor(88, 101, 242, 255));
    m_InfoReseau->append(QString::fromStdString(Contexte::GetInstance().getReseau()->getNom() +"\n"));
    m_InfoReseau->setTextColor(Qt::white);
    m_InfoReseau->append(QString::fromStdString(Contexte::GetInstance().informationsReseau()));

    m_InfoReseau->setReadOnly(true);
    lyt->addWidget(m_InfoReseau,0,1);
    wdg->show();
}
