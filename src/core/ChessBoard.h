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
#include "Piece.h"
#include "../util/Helper.h"

namespace Chess {
    struct BoardState {
        CastlingRights castlingRights;
        Square enPassantSquare;
        int halfMoveClock;
        int fullMoveNumber;
        Piece capturedPiece;
    };
    class ChessBoard {
    public:
        ChessBoard();
        // move methoden
        void makeMove(Move& move);
        void undoMove(Move& move);
        // getter
        Piece getPieceAt(Square square) const;
        Bitboard getAttackers(Square square);
        Color getSideToMove() const;
        // FEN helper
        std::string toFEN();
        void fromFEN(const std::string& fen);
        // game state helper
        bool isCheck() const;
        bool isCheckmate() const;
        bool isStalemate() const;
        bool isDraw() const;

        Bitboard getBitboard(Piece pieceType) const;
        Bitboard getBitboard(SimplePieceType piece, Color color) const;

        Bitboard getOccupied() const;
        Bitboard getOccupancy(Color color) const;
    private:
        // TODO: Zobrist Hashing

        void clear();
        void reset();
        void setPieceAt(Square square, Piece piece);
        void updateOccupancy();
        void switchColor();

        Bitboard m_pawns[2];
        Bitboard m_knights[2];
        Bitboard m_bishops[2];
        Bitboard m_rooks[2];
        Bitboard m_queens[2];
        Bitboard m_kings[2];

        Bitboard m_occupancy[2];    // Colors: white = 0, black = 1
        Bitboard m_occupied;        // all occupied squares  (b and w)
        Color m_sideToMove;

        BoardState m_boardState{};
        std::vector<BoardState> m_gameHistory;
    };

}


#endif //SCHACHENGINE_CHESSBOARD_H