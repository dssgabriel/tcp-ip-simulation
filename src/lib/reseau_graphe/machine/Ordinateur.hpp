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

#include <deque>
#include <cassert>

#include "Machine.hpp"
#include "../../../include/ParamInterface.hpp"
#include "../../../include/ElementControleCongestion.hpp"

class Ordinateur : public Machine {
    private:
        // Attributs
        static uint8_t m_NbOrdinateur;
        uint8_t m_IdOrdinateur;
        std::vector<ElementControleCongestion> m_ControleCongestion;

    public:
       // Constructeurs
        Ordinateur();

        // Destructeur
        ~Ordinateur();

        // Getters
        const uint8_t& getNbrOrdinateur() const;
        const uint8_t& getIdOrdinateur() const;
        inline void remettreIdAZero() { m_IdOrdinateur = 0; }

        const std::vector<ElementControleCongestion>&
            getControleCongestion() const;

        const ElementControleCongestion& getControleCongestion(
            const int& position
        ) const;


        // Methodes
        void remplirFileDonnees(
            const ParamInterface& config,
            const MAC& destination
        );

        void synchroniser();
        void finDeSession();

        virtual void envoyer(const uint32_t cwnd, const bool isAck);
        virtual void recevoir(const uint32_t cwnd, const bool isAck);
        
        void freeControleCongestion();

        void congestionAvoidance(std::bitset<16>& cwnd, uint16_t& ssthresh);
        void slowStart(std::bitset<16>& cwnd, uint16_t& ssthresh1);
        void fastRetransmit(const std::bitset<32>& seq, std::bitset<16>& cwnd, uint16_t& ssthresh);
        void fastRecovery(std::bitset<16>& cwnd, uint16_t& ssthresh);
};
