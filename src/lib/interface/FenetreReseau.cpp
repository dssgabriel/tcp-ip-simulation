#include "FenetreReseau.h"

FenetreReseau::FenetreReseau() : QHBoxLayout()
{
    // Creation du premier QHboxLayout
    m_F1 = new ChoixReseau();
    addLayout(m_F1);

    // Creation du deuxieme QHboxLayout
    m_F2 = new DonneeReseau();
    addLayout(m_F2);
}

// Destructeur //
FenetreReseau::~FenetreReseau() {

}
