//
// Created by augus on 23.12.2025.
//

#ifndef SCHACHENGINE_MOVEGENERATOR_H
#define SCHACHENGINE_MOVEGENERATOR_H
#include "ChessBoard.h"
#include "Movelist.h"

namespace Chess {
    class MoveGenerator {
    public:
        MoveGenerator() {
            initKnightAttacks();
            initPawnAttacks();
            initPawnPushes();
            initPawnDoublePushes();
            initKingAttacks();
            initRookRays();
            initBishopRays();
        }
        void generateLegalMoves(const ChessBoard& board,
                                   Movelist& moveList,
                                   Color sideToMove);
        void generatePseudoLegalMoves(const ChessBoard& board,
                                         Movelist& moveList,
                                         Color sideToMove);

        // nur zum testen
        void generateMovesFromSquare(const ChessBoard& board,
                                        Movelist& moveList,
                                        Square square,
                                        Color sideToMove);
    private:
        // bauern
        void generatePawnMoves(const ChessBoard& board,
                                  Movelist& moveList,
                                  Color color);

        void generatePawnNonCaptures(const ChessBoard& board,
                                            Movelist& moveList,
                                            Color color);

        void generatePawnCaptures(const ChessBoard& board,
                                         Movelist& moveList,
                                         Color color);

        void generatePawnPromotions(const ChessBoard& board,
                                           Movelist& moveList,
                                           Square from, Square to,
                                           bool isCapture);
        void generateEnPassantMoves(const ChessBoard& board,
                                       Movelist& moveList,
                                       Color color);
        // springer
        void generateKnightMoves(const ChessBoard& board,
                                    Movelist& moveList,
                                    Color color);
        // läufer
        void generateBishopMoves(const ChessBoard& board,
                                        Movelist& moveList,
                                        Color color);
        // türme
        void generateRookMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);

        // damen
        void generateQueenMoves(const ChessBoard& board,
                                       Movelist& moveList,
                                       Color color);

        // könige
        void generateKingMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);
        // rochade
        void generateCastlingMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);

        // HELPER-----------------------------------
        // TODO: ATTACK CHECK und precalculated attack tables
        void isSquareAttacked(const ChessBoard&, Square square, Color color);

        // filtert die illegalen aus der pseudolegal movelist
        void filterIllegalMoves(const ChessBoard& board,
                                   Movelist& moveList,
                                   Color sideToMove);
        bool canCastleKingside(const ChessBoard& board, Color color);
        bool canCastleQueenside(const ChessBoard& board, Color color);

        Color oppositeColor(Color color) {
            return (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
        }
        // Direction lookup-----------------------------
        // r is rank
        // f is file
        int knightDr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
        int knightDf[8] = {1, 2, 2, 1, -1, -2, -2, -1};

        // King
        int kingDr[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
        int kingDf[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        // Sliding
        int rookDr[4]   = { 1, -1, 0, 0 };
        int rookDf[4]   = { 0, 0, 1, -1 };

        int bishopDr[4] = { 1, 1, -1, -1 };
        int bishopDf[4] = { 1, -1, 1, -1 };

        // Attack Table---------------------------------
        Bitboard knightAttacks[64];
        Bitboard kingAttacks[64];
        Bitboard pawnAttacks[2][64];
        Bitboard pawnPushes[2][64];
        Bitboard pawnDoublePushes[2][64];
        Bitboard rookRays[64];
        Bitboard bishopRays[64];
        void initKnightAttacks() {
            for (int sq = 0; sq < 64; ++sq) {
                Bitboard attack = Bitboard{};

                int r = rankOf(sq);
                int f = fileOf(sq);

                for (int i = 0; i < 8; ++i) {
                    int rr = r + knightDr[i];
                    int ff = f + knightDf[i];

                    if (rr >= 0 && rr < 8 && ff >= 0 && ff < 8) {
                         attack |= 1ULL << (rr * 8 + ff);
                        // int bitIndex = rr*8 + ff;
                        // if (bitIndex >= 0 && bitIndex < 64) {
                        //     uint64_t bit = 1ULL << bitIndex;
                        //     attack |= Bitboard{bit};  // Verwenden Sie Bitboard-Konstruktor
                        //
                        //     std::cout << "  Adding bit " << bitIndex
                        //               << " (rank=" << rr << ", file=" << ff
                        //               << "), hex: 0x" << std::hex << bit << std::dec << "\n";
                        // } else {
                        //     std::cout << "ERROR: Invalid bitIndex " << bitIndex << "\n";
                        // }
                    }
                }

                knightAttacks[sq] = attack;
            }
        }
        void initKingAttacks() {
            for (int sq = 0; sq < 64; ++sq) {
                Bitboard bb;
                int r = rankOf(sq);
                int f = fileOf(sq);

                for (int i = 0; i < 8; ++i) {
                    int rr = r + kingDr[i];
                    int ff = f + kingDf[i];

                    if (rr >= 0 && rr < 8 && ff >= 0 && ff < 8)
                        bb |= 1ULL << (rr * 8 + ff);
                }

                kingAttacks[sq] = bb;
            }
        }
        void initPawnAttacks() {
            for (int sq = 0; sq < 64; ++sq) {
                int r = rankOf(sq);
                int f = fileOf(sq);

                Bitboard white;
                Bitboard black;

                // White pawns go UP (rank + 1)
                if (r < 7) {
                    if (f > 0) white |= 1ULL << ((r + 1) * 8 + (f - 1));
                    if (f < 7) white |= 1ULL << ((r + 1) * 8 + (f + 1));
                }

                // Black pawns go DOWN (rank - 1)
                if (r > 0) {
                    if (f > 0) black |= 1ULL << ((r - 1) * 8 + (f - 1));
                    if (f < 7) black |= 1ULL << ((r - 1) * 8 + (f + 1));
                }

                pawnAttacks[static_cast<int>(Color::WHITE)][sq] = white;
                pawnAttacks[static_cast<int>(Color::BLACK)][sq] = black;
            }
        }
        void initPawnPushes() {
            for (int sq = 0; sq < 64; ++sq) {
                int r = rankOf(sq);
                int f = fileOf(sq);

                // WHITE pawns (move north)
                if (r < 7) {  // Not on 8th rank
                    // Single push (always available if square ahead is empty)
                    pawnPushes[static_cast<int>(Color::WHITE)][sq] = Bitboard(1ULL << (sq + 8));
                } else {
                    pawnPushes[static_cast<int>(Color::WHITE)][sq] = Bitboard(0);
                }

                // BLACK pawns (move south)
                if (r > 0) {  // Not on 1st rank
                    pawnPushes[static_cast<int>(Color::BLACK)][sq] = Bitboard(1ULL << (sq - 8));
                } else {
                    pawnPushes[static_cast<int>(Color::BLACK)][sq] = Bitboard(0);
                }
            }
        }
        void initPawnDoublePushes() {
            for (int sq = 0; sq < 64; ++sq) {
                int r = rankOf(sq);
                int f = fileOf(sq);

                // WHITE pawns (from 2nd rank to 4th rank)
                if (r == 1) {  // On 2nd rank
                    pawnDoublePushes[static_cast<int>(Color::WHITE)][sq] = Bitboard(1ULL << (sq + 16));
                } else {
                    pawnDoublePushes[static_cast<int>(Color::WHITE)][sq] = Bitboard(0);
                }

                // BLACK pawns (from 7th rank to 5th rank)
                if (r == 6) {  // On 7th rank
                    pawnDoublePushes[static_cast<int>(Color::BLACK)][sq] = Bitboard(1ULL << (sq - 16));
                } else {
                    pawnDoublePushes[static_cast<int>(Color::BLACK)][sq] = Bitboard(0);
                }
            }
        }
        void initRookRays() {
            for (int sq = 0; sq < 64; ++sq) {
                Bitboard bb;
                int r = rankOf(sq);
                int f = fileOf(sq);

                for (int d = 0; d < 4; ++d) {
                    int rr = r;
                    int ff = f;

                    while (true) {
                        rr += rookDr[d];
                        ff += rookDf[d];

                        if (rr < 0 || rr > 7 || ff < 0 || ff > 7)
                            break;

                        bb |= 1ULL << (rr * 8 + ff);
                    }
                }

                rookRays[sq] = bb;
            }
        }
        void initBishopRays() {
            for (int sq = 0; sq < 64; ++sq) {
                Bitboard bb;
                int r = rankOf(sq);
                int f = fileOf(sq);

                for (int d = 0; d < 4; ++d) {
                    int rr = r;
                    int ff = f;

                    while (true) {
                        rr += bishopDr[d];
                        ff += bishopDf[d];

                        if (rr < 0 || rr > 7 || ff < 0 || ff > 7)
                            break;

                        bb |= 1ULL << (rr * 8 + ff);
                    }
                }

                bishopRays[sq] = bb;
            }
        }

    };
}

#endif //SCHACHENGINE_MOVEGENERATOR_H