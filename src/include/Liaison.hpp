#pragma once

#include <stdint.h>
#include <iostream>

struct Liaison {
    uint64_t m_Debit;
    uint16_t m_NumMachine1;
    uint16_t m_NumMachine2;

    friend std::ostream& operator<<(
        std::ostream& flux, 
        const Liaison& liaison
    ) {
        flux << liaison.m_NumMachine1 << " <- " << liaison.m_Debit;
        flux << " M -> " << liaison.m_NumMachine2;

        return flux;
    }
};