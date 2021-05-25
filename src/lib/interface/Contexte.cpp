/**
 * @file        Contexte.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe Contexte
 *
 * @author      Raphael LIN
 * @date        2021
 **/

#include "Contexte.hpp"

/**
 * @brief Constructeur de la classe Contexte
 *
 * Initialise le reseau en ouvrant le reseau simple par defaut.
 * Aucune donnee dans ParamInterface pour l'instant.
 * Le temps est initialise a 0.
 **/
Contexte::Contexte() {
    // Chargement du reseau Simple par defaut
    m_Reseau = nullptr;
    m_Config.m_Ssthresh = UINT16_MAX;
    m_Reseau = chargerReseau("../src/include/configReseau/ReseauEntreprise.json");
    AffichageReseau::GetInstance().configEntreprise();
    m_Temps = 0;
    m_TabCongestion = new std::vector<ElementControleCongestion>();
    ElementControleCongestion a; a.m_Mode = SlowStart; a.m_Temps=1; a.m_ValeurCwnd = 1;
    m_TabCongestion->push_back(a);
    ElementControleCongestion b; b.m_Mode = SlowStart; b.m_Temps=2; b.m_ValeurCwnd = 2;
    m_TabCongestion->push_back(b);
    ElementControleCongestion c; c.m_Mode = SlowStart; c.m_Temps=3; c.m_ValeurCwnd = 4;
    m_TabCongestion->push_back(c);
    ElementControleCongestion d; d.m_Mode = SlowStart; d.m_Temps=4; d.m_ValeurCwnd = 8;
    m_TabCongestion->push_back(d);
    ElementControleCongestion e; e.m_Mode = SlowStart; e.m_Temps=6; e.m_ValeurCwnd = 16;
    m_TabCongestion->push_back(e);
    ElementControleCongestion f; f.m_Mode = SlowStart; f.m_Temps=7; f.m_ValeurCwnd = 32;
    m_TabCongestion->push_back(f);
    ElementControleCongestion g; g.m_Mode = SlowStart; g.m_Temps=9; g.m_ValeurCwnd = 64;
    m_TabCongestion->push_back(g);
    ElementControleCongestion h; h.m_Mode = SlowStart; h.m_Temps=11; h.m_ValeurCwnd = 128;
    m_TabCongestion->push_back(h);
    ElementControleCongestion i; i.m_Mode = CongestionAvoidance; i.m_Temps=14; i.m_ValeurCwnd = 150;
    m_TabCongestion->push_back(i);
    ElementControleCongestion j; j.m_Mode = CongestionAvoidance; j.m_Temps=17; j.m_ValeurCwnd = 155;
    m_TabCongestion->push_back(j);
    ElementControleCongestion k; k.m_Mode = CongestionAvoidance; k.m_Temps=20; k.m_ValeurCwnd = 160;
    m_TabCongestion->push_back(k);
    ElementControleCongestion l; l.m_Mode = CongestionAvoidance; l.m_Temps=24; l.m_ValeurCwnd = 165;
    m_TabCongestion->push_back(l);
    ElementControleCongestion m; m.m_Mode = CongestionAvoidance; m.m_Temps=28; m.m_ValeurCwnd = 170;
    m_TabCongestion->push_back(m);
    ElementControleCongestion n; n.m_Mode = CongestionAvoidance; n.m_Temps=32; n.m_ValeurCwnd = 175;
    m_TabCongestion->push_back(n);
    ElementControleCongestion o; o.m_Mode = CongestionAvoidance; o.m_Temps=35; o.m_ValeurCwnd = 180;
    m_TabCongestion->push_back(o);
    ElementControleCongestion p; p.m_Mode = FastRetransmit; p.m_Temps=38; p.m_ValeurCwnd = 90;
    m_TabCongestion->push_back(p);
    ElementControleCongestion q; q.m_Mode = FastRecovery; q.m_Temps=42; q.m_ValeurCwnd = 95;
    m_TabCongestion->push_back(q);
    ElementControleCongestion r; r.m_Mode = FastRecovery; r.m_Temps=45; r.m_ValeurCwnd = 105;
    m_TabCongestion->push_back(r);
    ElementControleCongestion s; s.m_Mode = FastRecovery; s.m_Temps=50; s.m_ValeurCwnd = 115;
    m_TabCongestion->push_back(s);
    ElementControleCongestion t; t.m_Mode = FastRecovery; t.m_Temps=52; t.m_ValeurCwnd = 130;
    m_TabCongestion->push_back(t);
    ElementControleCongestion u; u.m_Mode = FastRetransmit; u.m_Temps=54; u.m_ValeurCwnd = 1;
    m_TabCongestion->push_back(u);
    ElementControleCongestion v; v.m_Mode = SlowStart; v.m_Temps=57; v.m_ValeurCwnd = 2;
    m_TabCongestion->push_back(v);
    ElementControleCongestion w; w.m_Mode = SlowStart; w.m_Temps=60; w.m_ValeurCwnd = 4;
    m_TabCongestion->push_back(w);
    ElementControleCongestion x; x.m_Mode = SlowStart; x.m_Temps=63; x.m_ValeurCwnd = 8;
    m_TabCongestion->push_back(x);
    ElementControleCongestion y; y.m_Mode = SlowStart; y.m_Temps=67; y.m_ValeurCwnd = 16;
    m_TabCongestion->push_back(y);
    ElementControleCongestion z; z.m_Mode = SlowStart; z.m_Temps=70; z.m_ValeurCwnd = 32;
    m_TabCongestion->push_back(z);
}

/**
 * @brief Getter pour recuperer le reseau
 *
 * @return Le ReseauGraphe
 **/
ReseauGraphe* Contexte::getReseau() {
    return m_Reseau.get();
}

/**
 * @brief Getter pour recuperer la configuration
 *
 * @return La configuration ParamInterface
 **/
ParamInterface& Contexte::getConfig() {
    return m_Config;
}

/**
 * @brief Getter pour recuperer l'adresse MAC d'arrivee
 *
 * @return L'adresse MAC d'arrivee
 **/
MAC& Contexte::getMACArrivee() {
    return m_Destination;
}

/**
 * @brief Getter pour recuperer le temps passe en millisecondes dans la simulation
 *
 * @return un entier representant le temps
 **/
int64_t& Contexte::getTemps() {
    return m_Temps;
}

/**
 * @brief Getter pour recuperer le vecteur d'ElementControleCongestion
 *
 * Il s'agit de la liste des transferts de paquets lors de la simulation.
 *
 * @return Le vecteur d'ElementControleCongestion
 **/
const std::vector<ElementControleCongestion>* Contexte::getTab() const {
    return m_TabCongestion;
}

/**
 * @brief Getter pour recuperer la map de temps paquet
 *
 * Il s'agit de la liste des temps des envois de paquets
 *
 * @return La map de temps paquet
 **/
const std::map<uint32_t, double> Contexte::getMap() const {
    return m_map;
}

/**
 * @brief Setter pour definir le reseau
 *
 * @param Reseau que l'on souhaite definir comme celui du contexte
 * @return void
 **/
void Contexte::setReseau(std::unique_ptr<ReseauGraphe>& newRes) {
    m_Reseau = std::move(newRes);
}

/**
 * @brief Fonction charger qui met a jour l'affichage de l'interface
 *
 * Cette fonction appelle la fonction config correspondante dans la classe AffichageReseau.
 * ELle appelle aussi la fonction analyseConfig de la classe ChoixReseau.
 *
 * @return void
 **/
void Contexte::charger() {
    //mise a jour de l'affichage
    if(m_Reseau->getNom() == "ReseauSimple") {
        AffichageReseau::GetInstance().configSimple();
    }
    else if(m_Reseau->getNom() == "ReseauMaison") {
        AffichageReseau::GetInstance().configMaison();
    }
    else if(m_Reseau->getNom() == "ReseauPME") {
        AffichageReseau::GetInstance().configPme();
    }
    else if(m_Reseau->getNom() == "ReseauEntreprise") {
        AffichageReseau::GetInstance().configEntreprise();
    }
    ChoixReseau::GetInstance().analyseConfig();
}

void Contexte::sauvegarder() {

}

/**
 * @brief Fonction exporterGraphe qui appelle sauvegarderGraphe de la classe AffichageReseau.
 *
 * Cette fonction transmet le chemin du fichier selectionne par l'utilisateur a la classe AffichageReseau.
 *
 * @param le chemin vers le fichier PNG de destination
 * @return void
 **/
void Contexte::exporterGraphe(const QString& nomFichier) {
    AffichageReseau::GetInstance().sauvegarderGraphe(nomFichier);
}

/**
 * @brief Fonction informationsReseau
 *
 * Cette fonction analyse les machines presentes dans le reseau et ecrit leurs informations dans un string.
 * ces informations sont le nom de la machine, son adresse IP, son adresse MAC et son Masque.
 *
 * @return le texte correspondant a la liste des machines du reseau et leurs informations.
 **/
std::string Contexte::informationsReseau() {
    std::string s;
    auto v = m_Reseau->getMachines();
    for(std::size_t i = 0; i < v.size(); ++i) {
        s += v[i]->getNom() + "\n";

        s += "ip: " + std::to_string(v[i]->getIp().a.to_ulong()) + "." + std::to_string(v[i]->getIp().b.to_ulong()) + "." +
                std::to_string(v[i]->getIp().c.to_ulong()) + "." + std::to_string(v[i]->getIp().d.to_ulong()) + "\n";

        s += "mac: " + std::to_string(v[i]->getMac().a.to_ulong()) + ":" + std::to_string(v[i]->getMac().b.to_ulong()) + ":" +
                std::to_string(v[i]->getMac().c.to_ulong()) + ":" + std::to_string(v[i]->getMac().d.to_ulong()) + ":" +
                std::to_string(v[i]->getMac().e.to_ulong()) + ":" + std::to_string(v[i]->getMac().f.to_ulong()) + "\n";

        s += "masque: " + std::to_string(v[i]->getMasque().a.to_ulong()) + "." + std::to_string(v[i]->getMasque().b.to_ulong()) + "." +
                std::to_string(v[i]->getMasque().c.to_ulong()) + "." + std::to_string(v[i]->getMasque().d.to_ulong()) + "\n\n";
    }
    return s;
}

/**
 * @brief Fonction chargerConfig qui permet de charger un reseau et actualiser l'affichage.
 *
 * Cette fonction charge le reseau choisi en parametre.
 * Elle appelle la fonction config correspondante dans la classe AffichageReseau.
 * ELle appelle aussi la fonction analyseConfig de la classe ChoixReseau.
 *
 * @param numero du reseau predefini de 1 a 4
 * @return le texte correspondant a la liste des machines du reseau et leurs informations.
 **/
void Contexte::chargerConfig(int numConfig) {
    m_Reseau->remettreIdAZero();
    m_Reseau.reset();
    if(numConfig == 1) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauSimple.json");
        AffichageReseau::GetInstance().configSimple();
    }
    else if(numConfig == 2) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauMaison.json");
        AffichageReseau::GetInstance().configMaison();
    }
    else if(numConfig == 3) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauPME.json");
        AffichageReseau::GetInstance().configPme();
    }
    else if(numConfig == 4) {
        m_Reseau = chargerReseau("../src/include/configReseau/ReseauEntreprise.json");
        AffichageReseau::GetInstance().configEntreprise();
    }
    ChoixReseau::GetInstance().analyseConfig();
    m_Reseau->lancerOSPF();
}

/**
 * @brief Fonction qui execute la simulation
 *
 * Cette fonction appelle l'initialisation du texte dans la classe ConfigReseau.
 * Elle appelle aussi l'initialisation du graphe dans la classe AffichageReseau.
 *
 * @return void
 **/
void Contexte::executerSimulation() {
    m_TabCongestion->clear();
    m_map.clear();

    Machine* m = m_Reseau->getMachine(m_Config.m_Source);
    Ordinateur* pc = dynamic_cast<Ordinateur*>(m);
    pc->freeControleCongestion();

    //
    Machine* m2 = m_Reseau->getMachine(m_Config.m_Destination);
    Ordinateur* pc2 = dynamic_cast<Ordinateur*>(m2);

    //
    pc->remplirFileDonnees(m_Config, pc2->getMac());

    //
    std::bitset<16> cwnd = 1;
    pc->lancerHorloge();
    pc->slowStart(cwnd, m_Config.m_Ssthresh);
    pc->arreterHorloge();
    *m_TabCongestion = pc->getControleCongestion();
    std::cout << "\n\nAffichage tableau controle congestion : \n";
    for (auto element : *m_TabCongestion){
        std::cout << "temps : " << element.m_Temps
            << ", valeur cwnd " << element.m_ValeurCwnd
            << " mode : " << element.m_Mode << std::endl;
    }

    //
    m_map = m_Reseau->getTempsPaquet();
    /*for (auto elt : m_map) {
        std::cout << "numpaquet : " << elt.first
            << ", temps : " << elt.second << " s\n";
    }*/
    ConfigReseau::GetInstance().initialiserTexte();
    AffichageReseau::GetInstance().initialiserGraphe();
}

/**
 * @brief Fonction qui rafraichit la simulation
 *
 * Cette fonction appelle le rafraichissement du texte dans la classe ConfigReseau.
 * Elle appelle aussi le rafraichissement du graphe dans la classe AffichageReseau.
 *
 * @return void
 **/
void Contexte::rafraichir() {
    ConfigReseau::GetInstance().rafraichirTexte();
    AffichageReseau::GetInstance().rafraichirGraphe();
}

void Contexte::stopSimulation() {

}

/**
 * @brief Destructeur de la classe Contexte
 *
 * Cette classe se supprime automatiquement avec le garbage collector
 **/
Contexte::~Contexte() {

}
