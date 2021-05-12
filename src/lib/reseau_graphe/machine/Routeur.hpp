#pragma once

#include <map>

#include "Machine.hpp"
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
        std::map<Routeur*, std::vector<Liaison*>*> m_TableRoutage;
        std::queue<PaquetOSPF> m_FilePaquetsOSPF;
        std::map<Routeur*, std::vector<std::bitset<32>>*> m_TableLSADemandes;
        std::map<Routeur*, std::vector<std::bitset<32>>*> m_TableLSAEnvoyes;

        // Methodes
        void traitementPaquetHello(const PaquetHello& hello);
        void traitementPaquetDBD(PaquetDBD& dbd);
        void traitementPaquetLSR(const PaquetLSR& lsr);
        void traitementPaquetLSU(const PaquetLSU& lsu);
        void traitementPaquetLSAck(const PaquetLSAck& ack);

    public:
        // Constructeurs
        Routeur();

        // Destructeur
        ~Routeur();

        // Getters
        uint8_t getNbRouteur();
        uint8_t getIdRouteur();
        //std::vector<Routeur> getRouteursVoisins();
        //const std::vector<Liaison> getPlusCourtChemin(Routeur& dest);

        // Methodes
        void envoyer(Routeur& dest, PaquetOSPF& ospf);
        void recevoir(PaquetOSPF& ospf);
        void traitementPaquetOSPF();

        void envoyer();
        void recevoir();
        void traitement(std::stack<std::bitset<16>> &donnee, MAC nouvelleDest);
};
