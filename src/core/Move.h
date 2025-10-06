//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_MOVE_H
#define SCHACHENGINE_MOVE_H

#pragma once
#include <cstdint>
#include "../util/Helper.h"

namespace Chess {
    class Move {
    public:
        // Konstruktoren
        Move(int from, int to, PieceType piece);
        Move(int from, int to, PieceType piece, PieceType captured);
        Move(int from, int to, PieceType piece, PieceType captured,
             PieceType promotion, MoveFlags flags);

        // Getter
        int fromSquare() const;
        int toSquare() const;
        PieceType piece() const;
        PieceType capturedPiece() const;
        PieceType promotionPiece() const;
        MoveFlags flags() const;

        // Flags Check
        bool isCapture() const;
        bool isPromotion() const;
        bool isEnPassant() const;
        bool isCastle() const;
        bool isDoublePawnPush() const;

        // Vergleichsoperatoren für Sorting
        bool operator<(const Move& other) const;
        bool operator==(const Move& other) const;
    private:
        uint32_t m_data;

        // für gute performance nur ein uint32_t mit allen informationen

        // bit layout
        // bits 0-5:   fromSquare (0-63)
        // bits 6-11:  toSquare (0-63)
        // bits 12-15: pieceType (0-11)
        // bits 16-19: capturedPiece (0-11)
        // bits 20-23: promotionPiece (0-11)
        // bits 24-27: moveFlags
        // bits 28-31: reserved

    };
}


#endif //SCHACHENGINE_MOVE_H