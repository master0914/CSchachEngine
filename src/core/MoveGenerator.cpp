//
// Created by augus on 23.12.2025.
//

#include "MoveGenerator.h"

namespace Chess {
    void MoveGenerator::generateLegalMoves(const ChessBoard &board, Movelist &moveList, Color sideToMove) {
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