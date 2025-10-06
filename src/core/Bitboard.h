//
// Created by augus on 26.09.2025.
//

#ifndef SCHACHENGINE_BITBOARD_H
#define SCHACHENGINE_BITBOARD_H
#pragma once
#include <cstdint>
#include "../util/Helper.h"

namespace Chess {


    class Bitboard {
    public:
        Bitboard();
        explicit Bitboard(uint64_t bits);
        void setBit(Square square);
        void clearBit(Square square);
        void toggleBit(Square square);
        bool getBit(Square square) const;

        Bitboard operator&(const Bitboard& other) const;
        Bitboard operator|(const Bitboard& other) const;
        Bitboard operator^(const Bitboard& other) const;
        Bitboard operator~() const;

        bool isEmpty() const;
        int popCount() const;  // wie biele bits gesetzt sind
        int lsb() const;       // lowest set bit
        int hsb() const;       // highest set bit
    private:
        uint64_t m_value;
    };
}

#endif //SCHACHENGINE_BITBOARD_H