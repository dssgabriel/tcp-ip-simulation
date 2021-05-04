#pragma once

#include <map>

#include "../../../include/ElementControleCongestion.hpp"
#include "../../../include/ParamInterface.hpp"
#include "Machine.hpp"

class Ordinateur : public Machine {
    private:
        // Attributs
        static uint8_t m_NbrOrdinateur;
        uint8_t m_IdOrdinateur;
        std::vector<ElementControleCongestion> m_ControleCongestion;
        std::map<uint16_t, double> m_TempsTraitementPaquet;
        
    public:
       // Constructeurs
        Ordinateur();
        // // Ordinateur(const std::string& nom);
        
        // Destructeur
        ~Ordinateur();
        
        // Getters
        const uint8_t& getNbrOrdinateur() const;
        const uint8_t& getIdOrdinateur() const;
        
        const std::vector<ElementControleCongestion>& 
            getControleCongestion() const;
            
        const ElementControleCongestion& getControleCongestion(
            const int& position
        ) const;
        
        const std::map<uint16_t, double>
            getTempsTraitementPaquet() const;
        double getTempsTraitementPaquet(
            const uint16_t& cle
        ) const;
        
        // Methodes
        void remplirFileDonnees(
            const ParamInterface& config,
            const MAC& destination
        );
        
        void synchroniser();
        void finDeSession();
        
        void envoyer();
        void recevoir();
        void traitement();
};