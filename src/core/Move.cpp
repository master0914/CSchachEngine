//
// Created by augus on 30.09.2025.
//

#include "Move.h"

namespace Chess {
    constexpr uint16_t FROM_MASK    = 0x003F;  // 0000 0000 0011 1111
    constexpr uint16_t TO_MASK      = 0x0FC0;  // 0000 1111 1100 0000
    constexpr uint16_t FLAGS_MASK   = 0xF000;  // 1111 0000 0000 0000

    constexpr int TO_SHIFT = 6;
    constexpr int FLAGS_SHIFT = 12;

    // Getter
    int Move::fromSquare() const {
        return m_data & FROM_MASK;
    }
    int Move::toSquare() const {
        return (m_data & TO_MASK) >> TO_SHIFT;
    }
    SimplePieceType Move::promotionPiece() const {
        uint8_t flags = static_cast<uint8_t>((m_data & FLAGS_MASK) >> FLAGS_SHIFT);

        switch (flags) {
            case Flag::PROMO_Q:
            case Flag::CAPTURE_PROMO_Q:
                return SimplePieceType::QUEEN;
            case Flag::PROMO_R:
            case Flag::CAPTURE_PROMO_R:
                return SimplePieceType::ROOK;
            case Flag::PROMO_B:
            case Flag::CAPTURE_PROMO_B:
                return SimplePieceType::BISHOP;
            case Flag::PROMO_N:
            case Flag::CAPTURE_PROMO_N:
                return SimplePieceType::KNIGHT;
            default:
                return SimplePieceType::NONE;
        }
    }
    Flag Move::flags() const {
        return static_cast<Flag>((m_data & FLAGS_MASK) >> FLAGS_SHIFT);
    }

    // Flags Check
    bool Move::isCapture() const{}
    bool Move::isPromotion() const{}
    bool Move::isEnPassant() const{}
    bool Move::isCastle() const{}
    bool Move::isDoublePawnPush() const{}

    // Vergleichsoperatoren für Sorting   (prb redundant)
    bool Move::operator<(const Move& other) const{}
    bool Move::operator==(const Move& other) const{}
}
