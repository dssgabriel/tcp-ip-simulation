#include "AffichageReseau.h"

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
    QPixmap pixmap("../src/lib/interface/ressources/Reseau4_Square.png");
    QIcon ButtonIcon(pixmap);
    m_Image->setIcon(ButtonIcon);
    m_Image->setMaximumSize(QSize(347, 700));
    m_Image->setIconSize(QSize(550, 550));
    addWidget(m_Image);

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

    m_Lignes[0]->append(0, 0);
    m_Lignes[0]->append(20, 5);
    addWidget(m_Vue);
}

// Destructeur //
AffichageReseau::~AffichageReseau() {

}
