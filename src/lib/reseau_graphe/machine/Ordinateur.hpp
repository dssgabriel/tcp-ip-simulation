/**
 * @file Ordinateur.hpp
 * @author Mickael Le Denmat
 * @brief Vous trouverez ici la declaration de la classe Ordinateur
 * @date 2021-05-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <map>
#include <deque>
#include <cassert>

#include "Machine.hpp"
#include "../../../include/ParamInterface.hpp"
#include "../../../include/ElementControleCongestion.hpp"

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
        
        const std::map<uint16_t, double> getTempsTraitementPaquet() const;

        double getTempsTraitementPaquet(const uint16_t& cle) const;
        
        // Methodes
        void remplirFileDonnees(
            const ParamInterface& config,
            const MAC& destination
        );
        
        void synchroniser();
        void finDeSession();
        
        virtual void envoyer(const uint32_t cwnd, const bool isAck);
        virtual void recevoir(const uint32_t cwnd, const bool isAck);

        void congestionAvoidance(std::bitset<16>& cwnd, uint16_t& ssthresh);
        void slowStart(std::bitset<16>& cwnd, uint16_t& ssthresh1);
        void fastRetransmit(const std::bitset<32>& seq, std::bitset<16>& cwnd, uint16_t& ssthresh);
        void fastRecovery(std::bitset<16>& cwnd, uint16_t& ssthresh);
};