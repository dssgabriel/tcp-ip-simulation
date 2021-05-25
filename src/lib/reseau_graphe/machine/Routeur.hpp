/**
 * @file    Routeur.hpp
 * @brief   Vous trouverez ici la declaration de la classe Ordinateur
 * @author  Mickael Le Denmat
 * @author  Gabriel Dos Santos
 * @date 2021-05-22
 *
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <map>
#include <deque>
#include <memory>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <cstdint>
#include <utility>

#include "Machine.hpp"
#include "Ordinateur.hpp"
#include "Commutateur.hpp"
#include "../ospf/PaquetDBD.hpp"
#include "../ospf/PaquetLSR.hpp"
#include "../ospf/PaquetLSU.hpp"
#include "../ospf/PaquetOSPF.hpp"
#include "../ospf/PaquetHello.hpp"
#include "../ospf/PaquetLSAck.hpp"
#include "../../../include/Liaison.hpp"

class Routeur : public Machine {
    private:
        // Attributs
        static uint16_t m_NbRouteur;
        uint16_t m_IdRouteur;
        std::map<Routeur*, std::vector<Liaison*>> m_TableRoutage;
        std::deque<PaquetOSPF*> m_FilePaquetsOSPF;
        std::map<Routeur*, std::vector<std::bitset<32>>> m_TableLSADemandes;
        std::map<Routeur*, std::vector<std::bitset<32>>> m_TableLSAEnvoyes;

        // Methodes
        void traitementPaquetHello(PaquetHello* hello);
        void traitementPaquetDBD(PaquetDBD* dbd);
        void traitementPaquetLSR(PaquetLSR* lsr);
        void traitementPaquetLSU(PaquetLSU* lsu);
        void traitementPaquetLSAck(PaquetLSAck* ack);

    public:
        // Constructeurs
        Routeur();

        // Destructeur
        ~Routeur();

        // Getters
        uint16_t getNbRouteur();
        uint16_t getIdRouteur();
        inline void remettreIdAZero() { m_IdRouteur = 0; }

        void setTableRoutage(Routeur* r, Liaison* l);
        std::map<Routeur*, std::vector<Liaison*>>& getTableRoutage();

        // Methodes
        MAC trouverMacDest(const IPv4 ip);
        void envoyerOSPF(Routeur* dest, PaquetOSPF* ospf);
        void recevoirOSPF(PaquetOSPF* ospf);
        void traitementPaquetOSPF();

        virtual void envoyer(const uint32_t cwnd, const bool isAck);
        virtual void recevoir(const uint32_t cwnd, const bool isAck);

        // Overloading
        friend std::ostream& operator<<(
            std::ostream& flux,
            Routeur& r
        );
};
