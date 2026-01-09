//
// Created by augus on 03.01.2026.
//

#ifndef SCHACHENGINE_ATTACKS_H
#define SCHACHENGINE_ATTACKS_H

#endif //SCHACHENGINE_ATTACKS_H
#pragma once
#include "../Bitboard.h"


namespace Chess {
    namespace CastlingMasks {
        // occupied mit diesen Masken AND
        constexpr uint64_t WHITE_KINGSIDE_EMPTY =
            (1ULL << toInt(Square::F1)) |
                (1ULL << toInt(Square::G1));
        constexpr uint64_t WHITE_QUEENSIDE_EMPTY =
            (1ULL << toInt(Square::B1)) |
                (1ULL << toInt(Square::C1)) |
                    (1ULL << toInt(Square::D1));
        constexpr uint64_t BLACK_KINGSIDE_EMPTY =
            (1ULL << toInt(Square::F8)) |
                (1ULL << toInt(Square::G8));
        constexpr uint64_t BLACK_QUEENSIDE_EMPTY =
            (1ULL << toInt(Square::B8)) |
                (1ULL << toInt(Square::C8)) |
                    (1ULL << toInt(Square::D8));

    }
    namespace Attacks{
        // Direction lookup-----------------------------
        // r is rank
        // f is file

        // knight
        constexpr int knightDr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
        constexpr int knightDf[8] = {1, 2, 2, 1, -1, -2, -2, -1};

        // King
        constexpr int kingDr[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
        constexpr int kingDf[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        // sliding
        constexpr int rookDr[4]   = { 1, -1, 0, 0 };
        constexpr int rookDf[4]   = { 0, 0, 1, -1 };
        // bishop
        constexpr int bishopDr[4] = { 1, 1, -1, -1 };
        constexpr int bishopDf[4] = { 1, -1, 1, -1 };

        // Attack Table---------------------------------
        // attack boards
        inline Bitboard knightAttacks[64];
        inline Bitboard kingAttacks[64];
        inline Bitboard pawnAttacks[2][64];
        inline Bitboard pawnPushes[2][64];
        inline Bitboard pawnDoublePushes[2][64];
        inline Bitboard rookRays[64];
        inline Bitboard bishopRays[64];

        // inits-----------------------------------------
        inline void initKnightAttacks() {
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
        inline void initKingAttacks() {
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
        inline void initPawnAttacks() {
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
        inline void initPawnPushes() {
            for (int sq = 0; sq < 64; ++sq) {
                int r = rankOf(sq);
                // int f = fileOf(sq);

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
        inline void initPawnDoublePushes() {
            for (int sq = 0; sq < 64; ++sq) {
                int r = rankOf(sq);
                // int f = fileOf(sq);

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
        inline void initRookRays() {
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
        inline void initBishopRays() {
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
        inline void init() {
            initKnightAttacks();
            initPawnAttacks();
            initPawnPushes();
            initPawnDoublePushes();
            initKingAttacks();
            initRookRays();
            initBishopRays();
        }
    }
}