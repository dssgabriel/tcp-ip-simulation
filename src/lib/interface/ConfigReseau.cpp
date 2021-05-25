/**
 * @file        ConfigReseau.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe ConfigReseau.
 *
 * @author      Jean-Christophe CHALAUD
 * @author      Raphael LIN
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
  *
  * @return void
  **/

void ConfigReseau::initialiserTexte(){
    m_FenetreDonnee->clear();
}

 /**
  * @brief Permet de rafrechir et de rajouter les informations voulues dans la QTextEdit.
  *
  *
  * @return void
  **/

void ConfigReseau::rafraichirTexte(){
	auto vector = Contexte::GetInstance().getTab();
	QString m_Texte;
	std::string m_Valeur;
    double m_Tempo = Contexte::GetInstance().getTemps()/2000;
	for (std::size_t i = 0; i < vector->size(); ++i) {
        if (m_Tempo >= (*vector)[i].m_Temps && m_Tempo - 0.1 < (*vector)[i].m_Temps) {
			if ((*vector)[i].m_Mode == SlowStart) {
                m_Valeur = "SlowStart - Taille de la fenetre cwnd: "+std::to_string((*vector)[i].m_ValeurCwnd)+
                ", Temps: "+std::to_string((*vector)[i].m_Temps)+" ms";
				m_FenetreDonnee->setTextColor(QColor(255,105,180,255));
				m_FenetreDonnee->append(m_Texte.fromStdString(m_Valeur));
			} else if ((*vector)[i].m_Mode == CongestionAvoidance) {
                m_Valeur = "Congestion Avoidance - Taille de la fenetre cwnd: "+std::to_string((*vector)[i].m_ValeurCwnd)+
                ", Temps: "+std::to_string((*vector)[i].m_Temps)+" ms";
				m_FenetreDonnee->setTextColor(Qt::cyan);
				m_FenetreDonnee->append(m_Texte.fromStdString(m_Valeur));
			} else if ((*vector)[i].m_Mode == FastRetransmit) {
                m_Valeur = "Fast Retransmit - Taille de la fenetre cwnd: "+std::to_string((*vector)[i].m_ValeurCwnd)+
                ", Temps: "+std::to_string((*vector)[i].m_Temps)+" ms";
				m_FenetreDonnee->setTextColor(QColor(138,43,226,255));
				m_FenetreDonnee->append(m_Texte.fromStdString(m_Valeur));
			} else if ((*vector)[i].m_Mode == FastRecovery) {
                m_Valeur = "Fast Recovery - Taille de la fenetre cwnd: "+std::to_string((*vector)[i].m_ValeurCwnd)+
                ", Temps: "+std::to_string((*vector)[i].m_Temps)+" ms";
				m_FenetreDonnee->setTextColor(Qt::green);
				m_FenetreDonnee->append(m_Texte.fromStdString(m_Valeur));

			}
		}
	}
}
