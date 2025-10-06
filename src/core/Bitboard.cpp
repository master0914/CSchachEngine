//
// Created by augus on 26.09.2025.
//

#include "Bitboard.h"

namespace Chess {
    Bitboard::Bitboard() {
        m_value = 0;
    }

    Bitboard::Bitboard(const uint64_t bits) {
        m_value = bits;
    }

    void Bitboard::setBit(const Square square) {
        // setzt den wert bei square immer auf 1
        m_value |= (1ULL << square);
    }

    void Bitboard::clearBit(const Square square) {
        // cleart bit so:   sq = 1
        // wenn board uint8 ist: vorher 00100010
        // 00100010 &= ~(00000010)  =
        // 00100010 &= 11111101     =
        // 00100000
        m_value &= ~(1ULL << square);
    }

    void Bitboard::toggleBit(const Square square) {
        // selbs prinzip wie bei setBit nur mit xor
        m_value ^= (1ULL << square);
    }

    bool Bitboard::getBit(const Square square) const {
        // shiftet das board so:   board = uint8 = 00010000    getbit(4)
        // board >> 4 = 0001
        // 1 & 1 = 1 = true
        return (m_value >> square) & 1;  // Shift und AND mit 1
    }

    Bitboard Bitboard::operator&(const Bitboard &other) const {
        return Bitboard{m_value & other.m_value};
    }

    Bitboard Bitboard::operator|(const Bitboard &other) const {
        return Bitboard{m_value | other.m_value};
    }

    Bitboard Bitboard::operator^(const Bitboard &other) const {
        return Bitboard{m_value ^ other.m_value};
    }

    Bitboard Bitboard::operator~() const {
        return Bitboard{~m_value};
    }

    bool Bitboard::isEmpty() const {
        return m_value == 0;
    }

    // danke an deepseek für die builtin methoden
    int Bitboard::popCount() const {
        return __builtin_popcount(m_value);
    }

    int Bitboard::lsb() const {
        return __builtin_ctzll(m_value);
    }

    int Bitboard::hsb() const {
        return 63 - __builtin_clzll(m_value);
    }
}
