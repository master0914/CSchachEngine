//
// Created by augus on 23.12.2025.
//

#include "MoveGenerator.h"

namespace Chess {
    void MoveGenerator::generateLegalMoves(const ChessBoard &board, Movelist &moveList, Color sideToMove) {
        generateKnightMoves(board, moveList, sideToMove);
    }

    void MoveGenerator::generatePseudoLegalMoves(const ChessBoard &board, Movelist &moveList, Color sideToMove) {
    }

    void MoveGenerator::generateMovesFromSquare(const ChessBoard &board, Movelist &moveList, Square square,
        Color sideToMove) {
    }

    void MoveGenerator::generatePawnMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generatePawnNonCaptures(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generatePawnCaptures(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generatePawnPromotions(const ChessBoard &board, Movelist &moveList, Square from, Square to,
        bool isCapture) {
    }

    void MoveGenerator::generateEnPassantMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generateKnightMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        Bitboard knights = board.getBitboard(SimplePieceType::KNIGHT, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(static_cast<Color>(!static_cast<bool>(color)));
        while (!knights.isEmpty()) {
            int from = knights.popLsb();
            Bitboard attacks = knightAttacks[from];
            attacks &= ~ownPieces;
            while (!attacks.isEmpty()) {
                int to  = attacks.popLsb();
                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    moveList.add(Move{from, to, CAPTURE});
                    LOG_INFO("added move");
                }else {
                    moveList.add(Move{from, to});
                    LOG_INFO("added move");
                }
            }
        }
    }

    void MoveGenerator::generateBishopMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generateRookMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generateQueenMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generateKingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generateCastlingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }
} // Chess