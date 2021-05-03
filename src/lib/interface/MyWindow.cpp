#include "MyWindow.h"

// Constructeur //
MyWindow::MyWindow() : QWidget()
{

    // Defintion de la fenetre de fond degrade noir vers gris, de taille initiale 500, 500, comportant un layout
    setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:2,   stop:0 rgba(10, 10, 10, 255), stop:1 rgba(70, 70, 70, 255))");
    resize(1280, 720);
    m_Vlayout = new QVBoxLayout();

    // Creation du premier QHboxLayout
    m_F1 = new MenuEntete();
    m_Vlayout->addLayout(m_F1);

    // Creation du deuxieme QHboxLayout
    m_F2 = new FenetreReseau();
    m_Vlayout->addLayout(m_F2);

    //Attribution du QVBoxLayout comme celui de mywindow
    setLayout(m_Vlayout);

}

// Destructeur //
MyWindow::~MyWindow() {

}

