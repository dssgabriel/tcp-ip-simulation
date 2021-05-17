#include "AffichageReseau.hpp"

AffichageReseau::AffichageReseau() : QHBoxLayout()
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

    m_Image = new QPushButton("");
    m_Image ->setStyleSheet(s);
    QPixmap pixmap("../src/lib/interface/ressources/Reseau1_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
    m_Image->setMaximumSize(QSize(347, 700));
    m_Image->setIconSize(QSize(347, 550));
    addWidget(m_Image);

    connect(m_Image,SIGNAL(clicked()),this,SLOT(informationsReseau()));

    m_Vue = new QChartView();
    m_Vue->setRenderHint(QPainter::Antialiasing);
    m_Vue->setStyleSheet("background-color: rgba(64, 68, 75, 255); border-radius: 5px; font: bold;");

    m_Graphique = m_Vue->chart();
    m_Graphique->setTitle("Controle de Congestion TCP/IP");
    m_Graphique->setTheme(QChart::ChartThemeDark);
    m_Graphique->titleFont().setBold(true);

    QLineSeries* slow_start = new QLineSeries();
    slow_start->setName("Slow Start");
    m_Lignes.push_back(slow_start);
    m_Graphique->addSeries(slow_start);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 200);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[0]->setColor(QColor(255,105,180,255));

    QLineSeries* cong_avoid = new QLineSeries();
    cong_avoid->setName("Congestion Avoidance");
    m_Lignes.push_back(cong_avoid);
    m_Graphique->addSeries(cong_avoid);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 200);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[1]->setColor(QColor(Qt::cyan));

    QLineSeries* fast_retransmit = new QLineSeries();
    fast_retransmit->setName("Fast Retransmit");
    m_Lignes.push_back(fast_retransmit);
    m_Graphique->addSeries(fast_retransmit);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 200);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[2]->setColor(QColor(138,43,226,255));

    QLineSeries* fast_recovery = new QLineSeries();
    fast_recovery->setName("Fast Recovery");
    m_Lignes.push_back(fast_recovery);
    m_Graphique->addSeries(fast_recovery);
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 200);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
    m_Lignes[3]->setColor(QColor(Qt::green));

    /*QLineSeries* initial = new QLineSeries();
    initial->setName("Slow Start");
    m_Lignes.push_back(initial);
    m_Graphique->addSeries(initial);


    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");


    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 21);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 6);

    m_Lignes[0]->setColor(QColor(255,105,180,255));
    m_Lignes[0]->append(0, 0);
    m_Lignes[0]->append(20, 5);

    QLineSeries* cong_avoid = new QLineSeries();
    cong_avoid->setName("Congestion Avoidance");
    m_Lignes.push_back(cong_avoid);
    m_Graphique->addSeries(cong_avoid);

    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 30);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 10);
    m_Lignes[1]->setColor(QColor(Qt::cyan));
    m_Lignes[1]->append(20, 5);
    m_Lignes[1]->append(22,5);
    m_Lignes[1]->append(26, 4);

    m_Lignes[0]->append(20, 5);
    m_Lignes[0]->append(22,5);
    m_Lignes[0]->append(26, 4);

    /*QLineSeries* slow2 = new QLineSeries();
    slow2->setName("Slow Start");
    m_Lignes.push_back(slow2);
    m_Graphique->addSeries(slow2);

    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 40);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 10);*/

    //m_Lignes[0]->append(27,6);
    addWidget(m_Vue);
}

// Destructeur //
AffichageReseau::~AffichageReseau() {

}

void AffichageReseau::configSimple()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau1_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);

}

void AffichageReseau::configMaison()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau2_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
}

void AffichageReseau::configPme()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau3_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
}

void AffichageReseau::configEntreprise()
{
    QPixmap pixmap("../src/lib/interface/ressources/Reseau4_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
}

void AffichageReseau::sauvegarderGraphe()
{
  QPixmap png_graphe = m_Vue->grab();
  QImage image = png_graphe.toImage();
  image.save("Graphique_congestion.png","PNG");
}

void AffichageReseau::informationsReseau()
{
    QWidget *wdg = new QWidget;
    wdg->setStyleSheet("background-color: rgba(44, 47, 51, 255);");
    QGridLayout* lyt = new QGridLayout();
    wdg->setLayout(lyt);
    QLabel* lbl = new QLabel();
    lbl->setPixmap(QPixmap("../src/lib/interface/ressources/simple.png"));
    lyt->addWidget(lbl,0,0);

    // QTextEdit + AddWidget //
    QTextEdit * m_InfoReseau = new QTextEdit();
    m_InfoReseau->setStyleSheet("background-color: rgba(64, 68, 75, 255); font: bold; border-radius: 5px;");
    m_InfoReseau->setTextColor(QColor(88, 101, 242, 255));
    m_InfoReseau->append("Reseau Simple\n");
    m_InfoReseau->setTextColor(Qt::white);
    m_InfoReseau->append
    (
        "ORDINATEUR 1:\n"
        "ip: 192.168.1.1\n" 
        "mac: 205-138-107-55-15-181\n"
         "masque: 255.255.255.0\n\n"
        
        "ORDINATEUR 2:\n"
            "ip: 192.168.1.2\n"
            "mac: 32-11-122-213-123-169\n"
            "masque: 255.255.255.0\n\n"

        "ORDINATEUR 3:\n"
            "ip: 192.168.1.127\n"
            "mac: 20-150-14-46-148-111\n"
            "masque: 255.255.255.0\n\n"

        "ORDINATEUR 4:\n"
            "ip: 192.168.1.128\n"
            "mac:6-8-182-75-181-255\n"
            "masque: 255.255.255.0\n\n"

        "ROUTEUR 1:\n"
            "ip: 192.168.1.65\n"
            "mac: 188-230-238-227-106-100\n"
            "masque: 255.255.255.0\n\n"

        "ROUTEUR 2:\n"
            "ip: 192.168.1.66\n"
            "mac: 81-216-176-118-154-102\n"
            "masque: 255.255.255.0\n"
    );
    //m_InfoReseau->setMaximumHeight(300);
    m_InfoReseau->setReadOnly(true);
    lyt->addWidget(m_InfoReseau,0,1);
    wdg->show();
}

void AffichageReseau::initialiserGraphe()
{
    m_Graphique->removeAllSeries();
    m_Graphique->createDefaultAxes();
    m_Graphique->axes(Qt::Horizontal).first()->setTitleText("Temps en ms");
    m_Graphique->axes(Qt::Vertical).first()->setTitleText("Fenetre cwnd");
    m_Graphique->axes(Qt::Horizontal).first()->setRange(0, 200);
    m_Graphique->axes(Qt::Vertical).first()->setRange(0, 200);
}
