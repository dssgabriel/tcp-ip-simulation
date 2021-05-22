/**
 * @file    Routeur.hpp
 * @brief   Declaration de la classe Routeur.
 * @author  Mickael Le Denmat
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#pragma once

#include <map>
#include <memory>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <cstdint>
#include <utility>

#include "Machine.hpp"
#include "Ordinateur.hpp"
#include "Commutateur.hpp"
#include "../ospf/PaquetOSPF.hpp"
#include "../ospf/PaquetHello.hpp"
#include "../ospf/PaquetDBD.hpp"
#include "../ospf/PaquetLSR.hpp"
#include "../ospf/PaquetLSU.hpp"
#include "../ospf/PaquetLSAck.hpp"
#include "../../../include/Liaison.hpp"

class Routeur : public Machine {
    private:
        // Attributs
        static uint8_t m_NbRouteur;
        uint8_t m_IdRouteur;
        std::map<Routeur*, std::vector<Liaison*>> m_TableRoutage;
        std::queue<PaquetOSPF*> m_FilePaquetsOSPF;
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
        uint8_t getNbRouteur();
        uint8_t getIdRouteur();

        // Methodes
        MAC trouverMacDest(const IPv4 ip);
        void envoyerOSPF(Routeur* dest, PaquetOSPF* ospf);
        void recevoirOSPF(PaquetOSPF* ospf);
        void traitementPaquetOSPF();

        virtual void envoyer(const uint32_t cwnd, const bool isAck);
        virtual void recevoir(const uint32_t cwnd, const bool isAck);
};
