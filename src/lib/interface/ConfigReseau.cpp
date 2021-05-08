#include "ConfigReseau.h"

ConfigReseau::ConfigReseau() : QHBoxLayout()
{
    m_FenetreDonnee = new QTextEdit();
    m_FenetreDonnee->setTextColor(Qt::blue);
    m_FenetreDonnee->append("le nombre de paquet recu est 258");
    m_FenetreDonnee->setTextColor(Qt::white);
    m_FenetreDonnee->append("les paquets sont de types HTTP");
    m_FenetreDonnee->setTextColor(Qt::red);
    m_FenetreDonnee->append("ils ont mis 300 msc");
    m_FenetreDonnee->setMaximumHeight(150);
    m_FenetreDonnee->setReadOnly(true);
    addWidget(m_FenetreDonnee);
    QPalette palette;
    palette.setColor(QPalette::Base, QColor(0, 0, 255, 255));
    m_FenetreDonnee->setPalette(palette);
}

// Destructeur //
ConfigReseau::~ConfigReseau() {

}
