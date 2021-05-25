#ifndef CONTEXTE_H
#define CONTEXTE_H

#include "AffichageReseau.hpp"
#include "ChoixReseau.hpp"
#include "ConfigReseau.hpp"
#include "../reseau_graphe/ReseauGraphe.hpp"
#include "../reseau_graphe/machine/Machine.hpp"
#include "../reseau_graphe/machine/Ordinateur.hpp"
#include "../reseau_graphe/machine/Commutateur.hpp"
#include "../reseau_graphe/machine/Routeur.hpp"
#include "../../include/ParamInterface.hpp"
#include "../../include/MAC.hpp"
#include "../../include/ElementControleCongestion.hpp"
#include "../gestion_fichiers/Chargement.hpp"
#include "../gestion_fichiers/Sauvegarde.hpp"

#include<memory>
#include<string>
#include<vector>
#include<QString>

class Contexte {
    private:
        // Attributs
        Contexte();

        std::unique_ptr<ReseauGraphe> m_Reseau;
        ParamInterface m_Config;
        MAC m_Destination;
        double m_Temps;
        std::vector<ElementControleCongestion>* m_TabCongestion;
        std::map<uint32_t, double> m_map;

    public:
        // Singleton
        static Contexte& GetInstance() {
            static Contexte singleton;
            return singleton;
        }

        // Méthodes de copie
        Contexte(Contexte&) = delete;
        void operator=(Contexte&) = delete;

        // Destructeur
        ~Contexte();

        // Getters
        ReseauGraphe* getReseau();
        ParamInterface& getConfig();
        MAC& getMACArrivee();
        double& getTemps();
        const std::vector<ElementControleCongestion>* getTab() const;
        const std::map<uint32_t, double> getMap() const;

        // Setter
        void setReseau(std::unique_ptr<ReseauGraphe>& newRes);

        // Méthodes
        void charger();
        void sauvegarder();
        void exporterGraphe(const QString& nomFichier);

        std::string informationsReseau();
        void chargerConfig(int numConfig);
        void chargementSimulation();

        void executerSimulation();
        void rafraichir();
        void stopSimulation();
};

#endif // CONTEXTE_H
