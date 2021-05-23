/**
 * @file        ConfigReseau.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe ConfigReseau.
 * 
 * @author      Jean-Christophe CHALAUD
 * @date        2021
 **/

#include "ConfigReseau.hpp"

 /**
  * @brief Constructeur de la classe ConfigReseau.
  * 
  * Le constructeur contient :
  * Une QTextEdit qui vas contenir des exemples de ce qui sera afficher par la suite.
  * Dans lequel les differentes lignes ont des couleurs deifferentes.
  * 
  **/

ConfigReseau::ConfigReseau() : QHBoxLayout()
{
    m_FenetreDonnee = new QTextEdit();
    m_FenetreDonnee->setStyleSheet("background-color: rgba(64, 68, 75, 255); border-radius: 5px;");
    m_FenetreDonnee->setTextColor(QColor(255,105,180,255));
    m_FenetreDonnee->append("Slow Start: 11 paquets envoyés - 5ms");
    m_FenetreDonnee->setTextColor(Qt::cyan);
    m_FenetreDonnee->append("Congestion Avoidance: 5 paquets envoyés - 3ms");
    m_FenetreDonnee->setTextColor(QColor(138,43,226,255));
    m_FenetreDonnee->append("Fast Retransmit: 2 paquets envoyés - 7ms");
    m_FenetreDonnee->setTextColor(Qt::green);
    m_FenetreDonnee->append("Fast Recovery: 3 paquets envoyés - 2ms");
    m_FenetreDonnee->setMaximumHeight(150);
    m_FenetreDonnee->setReadOnly(true);
    addWidget(m_FenetreDonnee);
    QPalette palette;
    palette.setColor(QPalette::Base, QColor(0, 0, 255, 255));
    m_FenetreDonnee->setPalette(palette);
}

/**
  * @brief Destructeur de la classe ConfigReseau.
  * 
  * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
  * 
  **/

ConfigReseau::~ConfigReseau(){

}

 /**
  * @brief Permet d'initialiser la QTextEdit.
  * 
  * Mise a null de toute la QTextEdit. 
  **/

void ConfigReseau::initialiserTexte(){
    m_FenetreDonnee->clear();
}

 /**
  * @brief Permet de rafrechir et de rajouter les informations voulu dans la QTextEdit.
  * 
  * Création d'une variable QString.
  * Convertion d'un std::string qui est retourner par la fonction informationsReseau() de la classe contexte
  * en un QString.
  * Ajout de ce QString au QTextEdit. 
  **/

void ConfigReseau::rafraichirTexte(){
    QString m_StringToQstring;
    m_StringToQstring.fromStdString(Contexte::GetInstance().informationsReseau());
    m_FenetreDonnee->append(m_StringToQstring);  
}
