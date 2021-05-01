#include <cstdint>
#include "IPv4.hpp"

enum TypePaquet: uint16_t {
    FTP, HTTP, SMTP, VTP
};

struct ParamInterface {
    IPv4 m_Source;
    IPv4 m_Destination;
    uint8_t m_Ssthresh;
    uint32_t m_NbPaquet;
    TypePaquet m_TypePaquet;
};
