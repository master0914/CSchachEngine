//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_HELPER_H
#define SCHACHENGINE_HELPER_H
#pragma once
#include <iostream>
#include <ostream>

#include "VectorUtil.h"

#endif //SCHACHENGINE_HELPER_H
#pragma once

namespace Chess {
    enum class Color: bool {
        WHITE = false,
        BLACK = true
    };
    // enum class PieceType : uint8_t {
    //     NO_PIECE = 0,
    //     WHITE_PAWN = 1,   // 0001
    //     WHITE_KNIGHT = 2, // 0010
    //     WHITE_BISHOP = 3, // 0011
    //     WHITE_ROOK = 4,   // 0100
    //     WHITE_QUEEN = 5,  // 0101
    //     WHITE_KING = 6,   // 0110
    //     BLACK_PAWN = 7,   // 0111
    //     BLACK_KNIGHT = 8, // 1000
    //     BLACK_BISHOP = 9, // 1001
    //     BLACK_ROOK = 10,  // 1010
    //     BLACK_QUEEN = 11, // 1011
    //     BLACK_KING = 12   // 1100
    // };
    enum class SimplePieceType : uint8_t {
        NONE = 0,
        PAWN = 1,
        KNIGHT = 2,
        BISHOP = 3,
        ROOK = 4,
        QUEEN = 5,
        KING = 6
    };
    enum Flag:uint8_t {
        NORMAL = 0x0,           // 0000
        CAPTURE = 0x1,          // 0001
        PROMO_Q = 0x2,          // 0010
        CAPTURE_PROMO_Q = 0x3,  // 0011
        PROMO_R = 0x4,          // 0100
        CAPTURE_PROMO_R = 0x5,  // 0101
        PROMO_B = 0x6,          // 0110
        CAPTURE_PROMO_B = 0x7,  // 0111
        PROMO_N = 0x8,          // 1000
        CAPTURE_PROMO_N = 0x9,  // 1001
        EN_PASSANT = 0xA,       // 1010
        CASTEL_KINGSIDE = 0xB,  // 1011
        CASTLE_QUEENSID = 0xC,  // 1100
        DOUBLE_PAWN_PUSH = 0xD  // 1101
        // 0xE und 0xF können noch für anderen shit verwendet werden
    };
    enum Square : uint8_t {
        A1 = 0,  B1 = 1,  C1 = 2,  D1 = 3,  E1 = 4,  F1 = 5,  G1 = 6,  H1 = 7,
        A2 = 8,  B2 = 9,  C2 = 10, D2 = 11, E2 = 12, F2 = 13, G2 = 14, H2 = 15,
        A3 = 16, B3 = 17, C3 = 18, D3 = 19, E3 = 20, F3 = 21, G3 = 22, H3 = 23,
        A4 = 24, B4 = 25, C4 = 26, D4 = 27, E4 = 28, F4 = 29, G4 = 30, H4 = 31,
        A5 = 32, B5 = 33, C5 = 34, D5 = 35, E5 = 36, F5 = 37, G5 = 38, H5 = 39,
        A6 = 40, B6 = 41, C6 = 42, D6 = 43, E6 = 44, F6 = 45, G6 = 46, H6 = 47,
        A7 = 48, B7 = 49, C7 = 50, D7 = 51, E7 = 52, F7 = 53, G7 = 54, H7 = 55,
        A8 = 56, B8 = 57, C8 = 58, D8 = 59, E8 = 60, F8 = 61, G8 = 62, H8 = 63,
        INVALID_SQUARE = 111
    };
    enum CastlingRights : uint8_t {
        NO_CASTLING = 0,
        WHITE_KINGSIDE  = 1 << 0,  // 0001:  weiß kurze Rochade
        WHITE_QUEENSIDE = 1 << 1,  // 0010: weiß lange Rochade
        BLACK_KINGSIDE  = 1 << 2,  // 0100: schwarz kurze Rochade
        BLACK_QUEENSIDE = 1 << 3   // 1000: schwarz lange Rochade
    };

    inline const std::string names[64] = {
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
    };
    inline std::string START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    // STRING-SQUARE
    inline std::string squareToString(Square const sq) {
        return names[sq];
    }
    inline Square stringToSquare(const std::string& str) {
        // danke deepseek(war zu faul)
        if(str.length() != 2) return INVALID_SQUARE;
        int file = str[0] - 'a';
        int rank = str[1] - '1';
        return static_cast<Square>(rank * 8 + file);
    }

    // BOard coord helper
    inline int XYtoBoardIndex(int x, int y) {
        // es wird naive angenommen dass x,y stimmt
        // vllt noch checks aber ich denke die fehler sind einfacher zu beheben,
        // wenn man sie in der funktion die diese hier aufruft überprüft da richtige dateiangabe gegeben ist
        return x * 8 + y;
    }
    inline int uiToBoardIndex(int uiX, int uiY) {
        // benötigt schon den UI-boardindex
        int boardY = 7 - uiY;
        return boardY * 8 + uiX;
    }

    inline Engine::vec2 boardIndexToUI(int boardIndex) {
        // gibt nur den UI-boardindex zurück
        int boardX = boardIndex % 8;
        int boardY = boardIndex / 8;
        int uiY = 7 - boardY;
        return Engine::vec2{static_cast<float>(boardX),static_cast<float>(uiY)};
    }
    // // STRING-PIECE
    // inline std::string pieceToChar(PieceType piece) {
    //     switch (piece) {
    //         case PieceType::NO_PIECE:
    //             return "";
    //         case PieceType::WHITE_PAWN:
    //             return "P";
    //         case PieceType::WHITE_KNIGHT:
    //             return "N";
    //         case PieceType::WHITE_BISHOP:
    //             return "B";
    //         case PieceType::WHITE_ROOK:
    //             return "R";
    //         case PieceType::WHITE_QUEEN:
    //             return "Q";
    //         case PieceType::WHITE_KING:
    //             return "K";
    //         case PieceType::BLACK_PAWN:
    //             return "p";
    //         case PieceType::BLACK_KNIGHT:
    //             return "n";
    //         case PieceType::BLACK_BISHOP:
    //             return "b";
    //         case PieceType::BLACK_ROOK:
    //             return "r";
    //         case PieceType::BLACK_QUEEN:
    //             return "q";
    //         case PieceType::BLACK_KING:
    //             return "k";
    //     }
    //     std::cerr << "Unknown piece type: " << static_cast<int>(piece) << std::endl;
    //     return "";
    // }
    // inline PieceType charToPiece(char c) {
    //     // danke an deepseek
    //     switch(c) {
    //         case 'P': return PieceType::WHITE_PAWN;
    //         case 'N': return PieceType::WHITE_KNIGHT;
    //         case 'B': return PieceType::WHITE_BISHOP;
    //         case 'R': return PieceType::WHITE_ROOK;
    //         case 'Q': return PieceType::WHITE_QUEEN;
    //         case 'K': return PieceType::WHITE_KING;
    //         case 'p': return PieceType::BLACK_PAWN;
    //         case 'n': return PieceType::BLACK_KNIGHT;
    //         case 'b': return PieceType::BLACK_BISHOP;
    //         case 'r': return PieceType::BLACK_ROOK;
    //         case 'q': return PieceType::BLACK_QUEEN;
    //         case 'k': return PieceType::BLACK_KING;
    //         default: return PieceType::NO_PIECE;
    //     }
    // }
    // // other piece help
    // inline Color getPieceColor(PieceType piece) {
    //     if(piece == PieceType::NO_PIECE) {return Color::White; }
    //     return (static_cast<int>(piece) < 6) ? Color::White : Color::Black;
    // }
}