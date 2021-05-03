#include "DonneeReseau.h"

DonneeReseau::DonneeReseau() : QVBoxLayout()
{
    // Creation du premier QHboxLayout
    m_F1 = new AffichageReseau();
    addLayout(m_F1);

    // Creation du deuxieme QHboxLayout
    m_F2 = new ConfigReseau();
    addLayout(m_F2);
}

// Destructeur //
DonneeReseau::~DonneeReseau() {

}
