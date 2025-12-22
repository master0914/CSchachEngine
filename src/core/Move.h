//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_MOVE_H
#define SCHACHENGINE_MOVE_H

#pragma once
#include <cstdint>

#include "Piece.h"
#include "../util/Helper.h"

namespace Chess {
    class Move {
    public:
        // Konstruktoren
        Move(int from, int to): m_data((from & 0x3F) | ((to & 0x3F) << 6)){}
        Move(int from, int to, Flag flag);

        // Getter
        int fromSquare() const;
        int toSquare() const;
        SimplePieceType promotionPiece() const;
        Flag flags() const;

        // Flags Check
        bool isCapture() const;
        bool isPromotion() const;
        bool isEnPassant() const;
        bool isCastle() const;
        bool isDoublePawnPush() const;

        // Vergleichsoperatoren für Sorting
        bool operator<(const Move& other) const;
        bool operator==(const Move& other) const;

        std::ostream& operator<<(std::ostream& os) const {
            return os << "MOVE: (" << fromSquare() << ", " << toSquare() << ")" << static_cast<int>(flags());
        }
    private:
        uint16_t m_data;

        // für gute performance nur ein uint16_t mit allen informationen

        // bit layout
        // bits 0-5:   fromSquare (0-63)  2^6
        // bits 6-11:  toSquare (0-63)    2^6
        // bits 12-15: flags (0-F hex)    2^4
        // Flags sind in Helper.h



    };
}


#endif //SCHACHENGINE_MOVE_H