//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_CHESSBOARD_H
#define SCHACHENGINE_CHESSBOARD_H
#pragma once
#include <string>
#include <vector>

#include "Bitboard.h"
#include "Move.h"
#include "../util/Helper.h"

namespace Chess {
    struct BoardState {
        CastlingRights castlingRights;
        Square enPassantSquare;
        int halfMoveClock;
        int fullMoveNumber;
        PieceType capturedPiece;
    };
    class ChessBoard {
    public:
        ChessBoard();
        // move methoden
        void makeMove(Move& move);
        void undoMove(Move& move);
        // getter
        PieceType getPieceAt(Square square);
        Bitboard getAttackers(Square square);
        // FEN helper
        std::string toFEN();
        void fromFEN(const std::string& fen);
        // game state helper
        bool isCheck() const;
        bool isCheckmate() const;
        bool isStalemate() const;
        bool isDraw() const;

        Bitboard getBitboard(PieceType pieceType) const;
    private:
        // TODO: Zobrist Hashing

        void clear();
        void reset();
        void setPieceAt(Square square, PieceType piece);
        void updateOccupancy();

        Bitboard m_bitboards[12];   // based on the piecetypes.   see: helper
        Bitboard m_occupancy[2];    // Colors: white = 0, black = 1
        Bitboard m_occupied;        // all occupied squares  (b and w)
        Color m_sideToMove;

        BoardState m_boardState{};
        std::vector<BoardState> m_gameHistory;
    };

}


#endif //SCHACHENGINE_CHESSBOARD_H