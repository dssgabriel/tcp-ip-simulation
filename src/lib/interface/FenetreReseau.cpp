#include "FenetreReseau.hpp"

FenetreReseau::FenetreReseau() : QHBoxLayout()
{
    // Creation du premier QHboxLayout
    addLayout(&ChoixReseau::GetInstance());

    // Creation du deuxieme QHboxLayout
    m_F2 = new DonneeReseau();
    addLayout(m_F2);
}

// Destructeur //
FenetreReseau::~FenetreReseau() {

}
