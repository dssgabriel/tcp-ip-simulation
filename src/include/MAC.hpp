#pragma once

#include <bitset>

struct MAC {
    std::bitset<8> a;
    std::bitset<8> b;
    std::bitset<8> c;
    std::bitset<8> d;
    std::bitset<8> e;
    std::bitset<8> f;
};

extern MAC macZero;
extern MAC macMax;