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
    };
    class ChessBoard {
    public:
        ChessBoard();
        // move methoden
        void makeMove(const Move& move);
        void undoMove();
        // getter
        [[nodiscard]] Piece getPieceAt(Square square) const;
        [[nodiscard]] Bitboard getAttackers(Square square);
        [[nodiscard]] Color getSideToMove() const;
        // FEN helper
        std::string toFEN();
        void fromFEN(const std::string& fen);
        // game state helper
        [[nodiscard]] bool isCheck() const;
        [[nodiscard]] bool isCheckmate() const;
        [[nodiscard]] bool isStalemate() const;
        [[nodiscard]] bool isDraw() const;

        [[nodiscard]] Bitboard getBitboard(Piece pieceType) const;
        [[nodiscard]] Bitboard getBitboard(SimplePieceType piece, Color color) const;

        [[nodiscard]] Bitboard getOccupied() const;
        [[nodiscard]] Bitboard getOccupancy(Color color) const;

        [[nodiscard]] CastlingRights getCastlingRights() const;
        [[nodiscard]] Square getEnPassantSquare() const;

        void debugPrint() const;
    private:
        // TODO: Zobrist Hashing

        void clear();
        void reset();
        void setPieceAt(Square square, Piece piece);
        void updateOccupancy();
        void switchColor();

        // kriegt das bewegte Piece übergeben
        void updateCastlingRights(Piece piece, Square from, Piece capturedPiece, Square to);


        // ist für unmove notwendig
        struct LastMoveInfo {
            Square from;
            Square to;
            Piece movedPiece;
            Piece capturedPiece; // EMPTY wenn kein Schlag
            BoardState boardState;
            bool undone = true;
        };


        Bitboard m_bitboards[2][6];

        Bitboard m_occupancy[2];    // Colors: white = 0, black = 1
        Bitboard m_occupied;        // all occupied squares  (b and w)

        BoardState m_boardState{};
        LastMoveInfo m_lastMove;
        Color m_sideToMove;




    };

}


#endif //SCHACHENGINE_CHESSBOARD_H