#include "ConfigReseau.hpp"

ConfigReseau::ConfigReseau() : QHBoxLayout()
{
    m_FenetreDonnee = new QTextEdit("Config Reseau");
    m_FenetreDonnee->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgba(0, 0, 0, 220), stop:1 rgba(100, 100, 100, 255)); "
                                    "border-radius: 5px; color: White; font: bold; font-size: 20px;");
    m_FenetreDonnee->setMaximumHeight(150);
    m_FenetreDonnee->setReadOnly(true);
    addWidget(m_FenetreDonnee);
}

// Destructeur //
ConfigReseau::~ConfigReseau() {

}
