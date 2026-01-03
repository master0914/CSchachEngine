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
        LOG_INFO("Generating knight moves:");
        generateKnightMoves(board, moveList, sideToMove);
        LOG_INFO("Generating knight moves over!" << std::endl);

        LOG_INFO("Generating Pawn moves:");
        generatePawnMoves(board, moveList, sideToMove);
        LOG_INFO("Generating pawn moves over!" << std::endl);

        LOG_INFO("Generating bishop moves:");
        generateBishopMoves(board, moveList, sideToMove);
        LOG_INFO("Generating bishop moves over" << std::endl);

        LOG_INFO("Generating rook moves:");
        generateRookMoves(board, moveList, sideToMove);
        LOG_INFO("Generating rook moves over" << std::endl);

        LOG_INFO("Generating queen moves:");
        generateQueenMoves(board, moveList, sideToMove);
        LOG_INFO("Generating queen moves over" << std::endl);

        LOG_INFO("Generating King moves:");
        generateKingMoves(board, moveList, sideToMove);
        LOG_INFO("Generating King moves over" << std::endl);
    }

    void MoveGenerator::generateMovesFromSquare(const ChessBoard &board, Movelist &moveList, Square square,
        Color sideToMove) {
    }

    // private methods--------------------------------------------------------------------------------------------
    // pawn stuff
    void MoveGenerator::generatePawnMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        LOG_INFO("Generating PawnNonCapture moves:");
        generatePawnNonCaptures(board, moveList, color);
        LOG_INFO("Generating PawnNonCapture moves over" << std::endl);

        LOG_INFO("Generating Capture moves:");
        generatePawnCaptures(board, moveList, color);
        LOG_INFO("Generating Capture moves over" << std::endl);
    }

    void MoveGenerator::generatePawnNonCaptures(const ChessBoard &board, Movelist &moveList, Color color) {

        // TODO promotions
        Bitboard ownPawns = board.getBitboard(SimplePieceType::PAWN, color);
        Bitboard allPieces   = board.getOccupied();
        while (!ownPawns.isEmpty()) {
            int from = ownPawns.popLsb();
            Bitboard normalPushes = Attacks::pawnPushes[static_cast<bool>(color)][from];
            Bitboard doublePushes = Attacks::pawnDoublePushes[static_cast<bool>(color)][from];
            normalPushes &= ~allPieces;
            while (!normalPushes.isEmpty()) {
                // es sollte nie ein enemy auf dem feld stehen weil die pushes schon mit der occupancy verrechnet wurden
                int to = normalPushes.popLsb();
                // hier dann promotion
                addMove(moveList,Move{from, to});
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
                        addMove(moveList,Move{from, to, Flag::DOUBLE_PAWN_PUSH});
                    }
                }
            }
        }
    }

    void MoveGenerator::generatePawnCaptures(const ChessBoard &board, Movelist &moveList, Color color) {
        // TODO auch hier promotions hinzufügen
        Bitboard ownPawns = board.getBitboard(SimplePieceType::PAWN, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(getOtherColor(color));
        while (!ownPawns.isEmpty()) {
            int from = ownPawns.popLsb();
            Bitboard pawnAttacks = Attacks::pawnAttacks[static_cast<bool>(color)][from];
            pawnAttacks &= ~ownPieces;
            while (!pawnAttacks.isEmpty()) {
                int to = pawnAttacks.popLsb();
                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    addMove(moveList,Move{from, to, Flag::CAPTURE});
                }
            }
        }
    }

    void MoveGenerator::generatePawnPromotions(const ChessBoard &board, Movelist &moveList, Square from, Square to,
        bool isCapture) {
    }

    void MoveGenerator::generateEnPassantMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    // knights
    void MoveGenerator::generateKnightMoves(const ChessBoard &board, Movelist &moveList, Color color) {

        Bitboard ownKnights = board.getBitboard(SimplePieceType::KNIGHT, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(getOtherColor(color));
        while (!ownKnights.isEmpty()) {
            int from = ownKnights.popLsb();
            Bitboard attacks = Attacks::knightAttacks[from];
            attacks &= ~ownPieces;
            while (!attacks.isEmpty()) {
                int to  = attacks.popLsb();
                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    addMove(moveList,Move{from, to, Flag::CAPTURE});
                }else {
                    addMove(moveList,Move{from, to});
                }
            }
        }

    }

    // bishops
    void MoveGenerator::generateBishopMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        // TODO "Classical Slider" und vllt wenn ich zeit und lust hab magic bitboards
        Bitboard ownBishops = board.getBitboard(SimplePieceType::BISHOP, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(getOtherColor(color));
        Bitboard allPieces   = board.getOccupied();
        while (!ownBishops.isEmpty()) {
            int from = ownBishops.popLsb();
            Bitboard attacks;

            // idee ist man durchläft alle richtungen bis man zum ende kommt
            for (int dir = 0; dir < 4; ++dir) {
                int rank = rankOf(from);
                int file = fileOf(from);
                while (true) {
                    rank += Attacks::bishopDr[dir];
                    file += Attacks::bishopDf[dir];

                    // entweder ende hier wegen out of bounds
                    if (rank < 0 || rank > 7 || file < 0 || file > 7)   break;

                    int to = rank * 8 + file;
                    attacks |= 1ULL << to;

                    // oder hier weil eine figur da steht
                    if (allPieces.getBit(static_cast<Square>(to))) {
                        break;
                    }
                }
            }

            // oben wird wenn eine figur dasteht standardmäßig ein angriff auf diese generiert
            // deshalb werden hier eigene figuren von den zügen entfernt
            attacks &= ~ownPieces;

            while (!attacks.isEmpty()) {
                int to = attacks.popLsb();

                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    addMove(moveList,Move{from, to, Flag::CAPTURE});
                } else {
                    addMove(moveList,Move{from, to});
                }
            }
        }
    }

    // rooks
    void MoveGenerator::generateRookMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        // eigendlich exact dasselbe wie Bishop
        // TODO "Classical Slider" und vllt wenn ich zeit und lust hab magic bitboards
        Bitboard ownRooks = board.getBitboard(SimplePieceType::ROOK, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(getOtherColor(color));
        Bitboard allPieces   = board.getOccupied();
        while (!ownRooks.isEmpty()) {
            int from = ownRooks.popLsb();
            Bitboard attacks;

            // idee ist man durchläft alle richtungen bis man zum ende kommt
            for (int dir = 0; dir < 4; ++dir) {
                int rank = rankOf(from);
                int file = fileOf(from);
                while (true) {
                    rank += Attacks::rookDr[dir];
                    file += Attacks::rookDf[dir];

                    // entweder ende hier wegen out of bounds
                    if (rank < 0 || rank > 7 || file < 0 || file > 7)   break;

                    int to = rank * 8 + file;
                    attacks |= 1ULL << to;

                    // oder hier weil eine figur da steht
                    if (allPieces.getBit(static_cast<Square>(to))) {
                        break;
                    }
                }
            }

            // oben wird wenn eine figur dasteht standardmäßig ein angriff auf diese generiert
            // deshalb werden hier eigene figuren von den zügen entfernt
            attacks &= ~ownPieces;

            while (!attacks.isEmpty()) {
                int to = attacks.popLsb();

                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    addMove(moveList,Move{from, to, Flag::CAPTURE});
                } else {
                    addMove(moveList,Move{from, to});
                }
            }
        }
    }

    // queen
    void MoveGenerator::generateQueenMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        // eigendlich exact dasselbe wie Bishop und rook
        // TODO "Classical Slider" und vllt wenn ich zeit und lust hab magic bitboards
        Bitboard ownQueens = board.getBitboard(SimplePieceType::QUEEN, color);
        // ja es sind queens man kann ja promoten XD
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(getOtherColor(color));
        Bitboard allPieces   = board.getOccupied();
        while (!ownQueens.isEmpty()) {
            int from = ownQueens.popLsb();
            Bitboard attacks;

            // idee ist man durchläft alle richtungen bis man zum ende kommt
            for (int dir = 0; dir < 4; ++dir) {
                int rank = rankOf(from);
                int file = fileOf(from);
                while (true) {
                    rank += Attacks::rookDr[dir];
                    file += Attacks::rookDf[dir];

                    // entweder ende hier wegen out of bounds
                    if (rank < 0 || rank > 7 || file < 0 || file > 7)   break;

                    int to = rank * 8 + file;
                    attacks |= 1ULL << to;

                    // oder hier weil eine figur da steht
                    if (allPieces.getBit(static_cast<Square>(to))) {
                        break;
                    }
                }
            }
            for (int dir = 0; dir < 4; ++dir) {
                int rank = rankOf(from);
                int file = fileOf(from);
                while (true) {
                    rank += Attacks::bishopDr[dir];
                    file += Attacks::bishopDf[dir];

                    // entweder ende hier wegen out of bounds
                    if (rank < 0 || rank > 7 || file < 0 || file > 7)   break;

                    int to = rank * 8 + file;
                    attacks |= 1ULL << to;

                    // oder hier weil eine figur da steht
                    if (allPieces.getBit(static_cast<Square>(to))) {
                        break;
                    }
                }
            }

            // oben wird wenn eine figur dasteht standardmäßig ein angriff auf diese generiert
            // deshalb werden hier eigene figuren von den zügen entfernt
            attacks &= ~ownPieces;

            while (!attacks.isEmpty()) {
                int to = attacks.popLsb();

                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    addMove(moveList,Move{from, to, Flag::CAPTURE});
                } else {
                    addMove(moveList,Move{from, to});
                }
            }
        }
    }

    // king
    void MoveGenerator::generateKingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        LOG_INFO("Generating Normal king moves");
        generateNormalKingMoves(board, moveList, color);
        LOG_INFO("Generating Normal king moves over" << std::endl);

        LOG_INFO("Generating Rochade moves");
        generateCastlingMoves(board, moveList, color);
        LOG_INFO("Generating Rochade moves over" << std::endl);
    }

    void MoveGenerator::generateNormalKingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
        Bitboard ownKing = board.getBitboard(SimplePieceType::KING, color);
        Bitboard ownPieces   = board.getOccupancy(color);
        Bitboard enemyPieces = board.getOccupancy(getOtherColor(color));
        while (!ownKing.isEmpty()) {
            int from = ownKing.popLsb();
            Bitboard attacks = Attacks::kingAttacks[from];
            attacks &= ~ownPieces;
            while (!attacks.isEmpty()) {
                int to  = attacks.popLsb();
                if (enemyPieces.getBit(static_cast<Square>(to))) {
                    addMove(moveList,Move{from, to, Flag::CAPTURE});
                }else {
                    addMove(moveList,Move{from, to});
                }
            }
        }
    }

    void MoveGenerator::generateCastlingMoves(const ChessBoard &board, Movelist &moveList, Color color) {
    }

    void MoveGenerator::addMove(Movelist &moveList, const Move &move) {
        // eig nur zum debuggen der LOG wird im release entfernt
        LOG_INFO("adding move: " << move);
        moveList.add(move);
    }
}
