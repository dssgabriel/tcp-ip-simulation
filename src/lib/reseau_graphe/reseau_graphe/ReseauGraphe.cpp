#include "ReseauGraphe.hpp"
#include "machine/Routeur.hpp"
#include <cstdlib>

ReseauGraphe::ReseauGraphe() {
    m_Machines.clear();
    m_Liaisons.clear();
}

ReseauGraphe::~ReseauGraphe() {
}

// Getters & setters
void ReseauGraphe::setNom(const std::string nom) {
    m_Nom = nom;
}

const std::string& ReseauGraphe::getNom() const{
    return m_Nom;
}

Machine& ReseauGraphe::getMachine(const IPv4& ip) {
   for(size_t i = 0; i < m_Machines.size(); ++i) {
       if(m_Machines[i].getIp() == ip) {
           return m_Machines[i];
       }
   }

    std::cout << "ERREUR : Adresse IP <" << ip;
    std::cout << "> introuvable sur le reseau.\n";
    exit(EXIT_FAILURE);
}

const std::vector<Machine>& ReseauGraphe::getMachines() const {
    return m_Machines;
}

const std::vector<Liaison>& ReseauGraphe::getLiaisons() const {
    return m_Liaisons;
}

// Overloading
std::ostream& operator<<(std::ostream& flux, const ReseauGraphe& reseau) {
    flux << "Nom du réseau : " << reseau.getNom() << "\n";

    // Affichage de la liste des machines.
    std::vector<Machine> cpyMachines = reseau.getMachines();
    for(Machine m : cpyMachines) {
        flux << m << "\n";
    }

    // Affichage de la liste des liaisons.
    std::vector<Liaison> cpyLiaisons = reseau.getLiaisons();
    for(Liaison l : cpyLiaisons) {
        flux << l << "\n";
    }

    return flux;
}

// Methodes
void DFS(int v, bool visiter[]) 
{   
    visiter[v] = true; 
   
    for(int i = 0; i < size().m_Liaisons; ++i){
        if(!visiter[*i]){
        DFS_util(*i, visiter);
        }
    } 
} 

bool ReseauGraphe::estConnexe() {
    bool connexe = false;
    int V = size().m_Machines;
    bool *visiter = new bool[V];
    
    for(int i = 0; i < V; i++){
        visiter[i] = false;
    }

    for(int i = 0; i < V; i++){
        if(visiter[i] = false){
            DFS(i,vister);
        }
    }

    return connexe;
}

void ReseauGraphe::ajouter(Machine m) {
    m_Machines.emplace_back(m);
}

void ReseauGraphe::ajouter(Liaison l) {
    m_Liaisons.emplace_back(l);
}

void ReseauGraphe::routageDynamique() {

}
