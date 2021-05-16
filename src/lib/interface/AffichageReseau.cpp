#include "AffichageReseau.hpp"

AffichageReseau::AffichageReseau() : QHBoxLayout()
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

    m_Image = new QPushButton("");
    m_Image ->setStyleSheet(s);
    QPixmap pixmap("../src/lib/interface/ressources/Reseau4_Rectangle.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
    m_Image->setMaximumSize(QSize(347, 700));
    m_Image->setIconSize(QSize(347, 550));
    addWidget(m_Image);

    connect(m_Image,SIGNAL(clicked()),this,SLOT(informationsReseau()));

    m_Vue = new QChartView();
    m_Vue->setRenderHint(QPainter::Antialiasing);
    m_Vue->setStyleSheet("background-color: rgba(50, 50, 50, 255); border-radius: 5px; font: bold;");

    m_Graphique = m_Vue->chart();
    m_Graphique->setTitle("Controle de Congestion TCP/IP");
    m_Graphique->setTheme(QChart::ChartThemeDark);
    m_Graphique->titleFont().setBold(true);

    QLineSeries* initial = new QLineSeries();
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

    m_Lignes[0]->append(27,6);

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
    QWidget* window = new QWidget;
    QLabel* test = new QLabel;
    test->setPixmap(QPixmap("../src/lib/interface/ressources/Reseau4_Rectangle.png"));
    window->resize(600, 600);
    test->show();
    window->show();
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