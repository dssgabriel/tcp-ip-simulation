#pragma once

#include <bitset>

struct MAC {
    std::bitset<8> a;
    std::bitset<8> b;
    std::bitset<8> c;
    std::bitset<8> d;
    std::bitset<8> e;
    std::bitset<8> f;

        bool operator==(const MAC& mac) const {
        return (
              (a.to_ulong() == mac.a.to_ulong())
            & (b.to_ulong() == mac.b.to_ulong())
            & (c.to_ulong() == mac.c.to_ulong())
            & (d.to_ulong() == mac.d.to_ulong())
            & (e.to_ulong() == mac.e.to_ulong())
            & (f.to_ulong() == mac.f.to_ulong())
        );
    }
};

extern MAC macZero;
extern MAC macMax;