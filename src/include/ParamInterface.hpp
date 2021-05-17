#pragma once

#include <cstdint>
#include "IPv4.hpp"

enum TypeFichier: uint16_t {
    FTP, HTTP, SMTP, VTP
};

struct ParamInterface {
    IPv4 m_Source;
    IPv4 m_Destination;
    uint16_t m_Ssthresh;
    uint32_t m_NbPaquet;
    TypeFichier m_TypeFichier;
};
