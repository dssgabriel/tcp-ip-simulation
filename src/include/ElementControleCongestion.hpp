#include <bits/stdint-uintn.h>
#include <cstdint>

enum ModeCongestion {
    SlowStart, CongestionAvoidance, FastRetransmit, FastRecovery
};

struct ElementControleCongestion {
    double m_Temps;
    uint16_t m_ValeurCwnd;
    ModeCongestion m_Mode;
};
