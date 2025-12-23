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
            case PROMO_Q:
            case CAPTURE_PROMO_Q:
                return SimplePieceType::QUEEN;
            case PROMO_R:
            case CAPTURE_PROMO_R:
                return SimplePieceType::ROOK;
            case PROMO_B:
            case CAPTURE_PROMO_B:
                return SimplePieceType::BISHOP;
            case PROMO_N:
            case CAPTURE_PROMO_N:
                return SimplePieceType::KNIGHT;
            default:
                return SimplePieceType::NONE;
        }
    }
    Flag Move::flags() const {
        return static_cast<Flag>((m_data & FLAGS_MASK) >> FLAGS_SHIFT);
    }

    // Flags Check
    bool Move::isCapture() const{
        uint8_t f = flags();
        return f == CAPTURE ||
               f == CAPTURE_PROMO_Q || f == CAPTURE_PROMO_R ||
               f == CAPTURE_PROMO_B || f == CAPTURE_PROMO_N ||
               f == EN_PASSANT;
    }
    bool Move::isPromotion() const{
        uint8_t f = flags();
        // promotion flags: 0x2-0x9
        return f >= PROMO_Q && f <= CAPTURE_PROMO_N;
    }
    bool Move::isEnPassant() const{
        return flags() == EN_PASSANT;
    }
    bool Move::isCastle() const{
        uint8_t f = flags();
        return f == CASTEL_KINGSIDE || f == CASTLE_QUEENSID;
    }
    bool Move::isDoublePawnPush() const{
        return flags() == DOUBLE_PAWN_PUSH;
    }

    // Vergleichsoperatoren für Sorting   (prb redundant)
    bool Move::operator<(const Move& other) const{}
    bool Move::operator==(const Move& other) const{}

    bool Move::isValid() const { return m_data != 0; }
}
