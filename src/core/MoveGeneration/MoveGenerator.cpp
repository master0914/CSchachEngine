//
// Created by augus on 23.12.2025.
//

#include "MoveGenerator.h"

#include "Attacks.h"

namespace Chess {
    // public methdos-----------------------------------------------------------------------------------------
    void MoveGenerator::generateLegalMoves(const ChessBoard &board, Movelist &moveList, Color sideToMove) {
        generatePseudoLegalMoves(board, moveList, sideToMove);
    }

    void MoveGenerator::generatePseudoLegalMoves(const ChessBoard &board, Movelist &moveList, Color sideToMove) {
        generateKnightMoves(board, moveList, sideToMove);
        generatePawnMoves(board, moveList, sideToMove);
    }

    void MoveGenerator::generateMovesFromSquare(const ChessBoard &board, Movelist &moveList, Square square,
        Color sideToMove) {
    }

    // private methods--------------------------------------------------------------------------------------------
    // pawn stuff
    void MoveGenerator::generatePawnMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        generatePawnNonCaptures(board, moveList, color);
    }

    void MoveGenerator::generatePawnNonCaptures(const ChessBoard &board, Movelist &moveList, Color color) {
        LOG_INFO("Generating Pawn moves:");
        // TODO promotions
        Bitboard pawns = board.getBitboard(SimplePieceType::PAWN, color);
        Bitboard allPieces   = board.getOccupied();
        while (!pawns.isEmpty()) {
            int from = pawns.popLsb();
            Bitboard normalPushes = Attacks::pawnPushes[static_cast<bool>(color)][from];
            Bitboard doublePushes = Attacks::pawnDoublePushes[static_cast<bool>(color)][from];
            normalPushes &= ~allPieces;
            while (!normalPushes.isEmpty()) {
                // es sollte nie ein enemy auf dem feld stehen weil die pushes schon mit der occupancy verrechnet wurden
                int to = normalPushes.popLsb();
                // hier dann promotion
                moveList.add(Move{from, to});
                LOG_INFO("added move{" << from << ", " << to << "}");
            }
            bool isOnStartingRank = false;
            if (color == Color::WHITE) {
                isOnStartingRank = (from >= toInt(Square::A2) && from <= toInt(Square::H2));
            } else {
                isOnStartingRank = (from >= toInt(Square::A7) && from <= toInt(Square::H7));
            }
            if (isOnStartingRank && !doublePushes.isEmpty()) {
                // felt zwischen from und to
                int intermediateSquare = from + ((color == Color::WHITE) ? 8 : -8);
                if (!allPieces.getBit(static_cast<Square>(intermediateSquare))) {
                    doublePushes &= ~allPieces;
                    while (!doublePushes.isEmpty()) {
                        int to = doublePushes.popLsb();
                        moveList.add(Move{from, to, Flag::DOUBLE_PAWN_PUSH});
                        LOG_INFO("added move{" << from << ", " << to << "} double Pawn Push: " << static_cast<int>(Flag::DOUBLE_PAWN_PUSH));
                    }
                }
            }
        }
    }

    void MoveGenerator::generatePawnCaptures(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generatePawnPromotions(const ChessBoard &board, Movelist &moveList, Square from, Square to,
        bool isCapture) {
    }

    void MoveGenerator::generateEnPassantMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    // knights
    void MoveGenerator::generateKnightMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        LOG_INFO("Generating knight moves:");
        Bitboard knights = board.getBitboard(SimplePieceType::KNIGHT, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(static_cast<Color>(!static_cast<bool>(color)));
        while (!knights.isEmpty()) {
            int from = knights.popLsb();
            Bitboard attacks = Attacks::knightAttacks[from];
            attacks &= ~ownPieces;
            while (!attacks.isEmpty()) {
                int to  = attacks.popLsb();
                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    moveList.add(Move{from, to, Flag::CAPTURE});
                    LOG_INFO("added move{" << from << ", " << to << "}" << static_cast<int>(Flag::CAPTURE));
                }else {
                    moveList.add(Move{from, to});
                    LOG_INFO("added move{" << from << ", " << to << "}");
                }
            }
        }
        LOG_INFO("knight moves over!" << std::endl);
    }

    // bishops
    void MoveGenerator::generateBishopMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    // rooks
    void MoveGenerator::generateRookMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    // queen
    void MoveGenerator::generateQueenMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    // king
    void MoveGenerator::generateKingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::generateCastlingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }
}