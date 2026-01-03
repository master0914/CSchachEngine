//
// Created by augus on 26.09.2025.
//

#include "Bitboard.h"

namespace Chess {
    Bitboard::Bitboard() {
        m_value = 0ULL;
    }

    Bitboard::Bitboard(const uint64_t bits) {
        m_value = bits;
    }

    void Bitboard::setBit(const Square square) {
        // setzt den wert bei square immer auf 1
        m_value |= (1ULL << toInt(square));
    }

    void Bitboard::clearBit(const Square square) {
        // cleart bit so:   sq = 1
        // wenn board uint8 ist: vorher 00100010
        // 00100010 &= ~(00000010)  =
        // 00100010 &= 11111101     =
        // 00100000
        m_value &= ~(1ULL << toInt(square));
    }

    void Bitboard::toggleBit(const Square square) {
        // selbs prinzip wie bei setBit nur mit xor
        m_value ^= (1ULL << toInt(square));
    }

    bool Bitboard::getBit(const Square square) const {
        // shiftet das board so:   board = uint8 = 00010000    getbit(4)
        // board >> 4 = 0001
        // 1 & 1 = 1 = true
        return (m_value >> toInt(square)) & 1;  // Shift und AND mit 1
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
    Bitboard Bitboard::operator&(const uint64_t other) const {
        return Bitboard{m_value & other};
    }

    Bitboard Bitboard::operator|(const uint64_t other) const {
        return Bitboard{m_value | other};
    }

    Bitboard Bitboard::operator^(const uint64_t other) const {
        return Bitboard{m_value ^ other};
    }
    Bitboard& Bitboard::operator&=(const Bitboard &other) {
        m_value &= other.m_value;
        return *this;
    }
    Bitboard& Bitboard::operator|=(const Bitboard &other) {
        m_value |= other.m_value;
        return *this;
    }
    Bitboard& Bitboard::operator^=(const Bitboard &other) {
        m_value ^= other.m_value;
        return *this;
    }
    Bitboard& Bitboard::operator&=(const uint64_t other) {
        m_value &= other;
        return *this;
    }
    Bitboard& Bitboard::operator|=(const uint64_t other) {
        m_value |= other;
        return *this;
    }
    Bitboard& Bitboard::operator^=(const uint64_t other) {
        m_value ^= other;
        return *this;
    }
    Bitboard& Bitboard::operator<<=(int shift) {
        m_value <<= shift;
        return *this;
    }
    Bitboard& Bitboard::operator>>=(int shift) {
        m_value >>= shift;
        return *this;
    }

    bool Bitboard::isEmpty() const {
        return m_value == 0;
    }

    // danke an deepseek für die builtin methoden
    int Bitboard::popCount() const {
        return __builtin_popcount(m_value);
    }
    int Bitboard::popLsb() {
        // Zuerst den Index des LSB ermitteln
        int index = __builtin_ctzll(m_value);
        // Dann das Bit löschen (setze niedrigstes gesetztes Bit auf 0)
        m_value &= m_value - 1;
        return index;
    }

    int Bitboard::lsb() const {
        return __builtin_ctzll(m_value);
    }

    int Bitboard::hsb() const {
        return 63 - __builtin_clzll(m_value);
    }

    void Bitboard::debugPrint() const {
        for (int rank = 0; rank < 8; ++rank) {          // 8 → 1
            for (int file = 0; file < 8; ++file) {       // a → h
                int bitIndex = rank * 8 + file;
                bool isSet = (m_value >> bitIndex) & 1ULL;

                std::cout << (isSet ? "1 " : ". ");
            }
            std::cout << '\n';
        }
    }

    uint64_t Bitboard::getValue() const {
        return m_value;
    }
}
