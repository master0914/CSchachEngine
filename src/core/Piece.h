//
// Created by augus on 22.12.2025.
//

#ifndef SCHACHENGINE_PIECE_H
#define SCHACHENGINE_PIECE_H
#include <cstdint>

#include "../util/Helper.h"

namespace Chess {
    class Piece {
    public:
        Piece() : m_data(0) {} // NONE, keine Farbe
        Piece(Color color, SimplePieceType type)
            : m_data((static_cast<uint8_t>(color) << 3) | static_cast<uint8_t>(type)) {}
        Piece(char c) {
            // danke deepseek
            switch (c) {
                case 'P': m_data = (0 << 3) | 1; break; // White pawn
                case 'N': m_data = (0 << 3) | 2; break; // White knight
                case 'B': m_data = (0 << 3) | 3; break; // White bishop
                case 'R': m_data = (0 << 3) | 4; break; // White rook
                case 'Q': m_data = (0 << 3) | 5; break; // White queen
                case 'K': m_data = (0 << 3) | 6; break; // White king
                case 'p': m_data = (1 << 3) | 1; break; // Black pawn
                case 'n': m_data = (1 << 3) | 2; break; // Black knight
                case 'b': m_data = (1 << 3) | 3; break; // Black bishop
                case 'r': m_data = (1 << 3) | 4; break; // Black rook
                case 'q': m_data = (1 << 3) | 5; break; // Black queen
                case 'k': m_data = (1 << 3) | 6; break; // Black king
                default:  m_data = 0; break; // Empty
            }
        }

        bool isEmpty() const { return type() == SimplePieceType::NONE; }
        Color color() const { return static_cast<Color>(m_data >> 3); }
        SimplePieceType type() const { return static_cast<SimplePieceType>(m_data & 0x07); }

        bool operator==(const Piece& other) const { return m_data == other.m_data; }
        bool operator!=(const Piece& other) const { return m_data != other.m_data; }

        char toChar() const {
            if (isEmpty()) return '.';

            char c;
            switch (type()) {
                case SimplePieceType::PAWN:   c = 'p'; break;
                case SimplePieceType::KNIGHT: c = 'n'; break;
                case SimplePieceType::BISHOP: c = 'b'; break;
                case SimplePieceType::ROOK:   c = 'r'; break;
                case SimplePieceType::QUEEN:  c = 'q'; break;
                case SimplePieceType::KING:   c = 'k'; break;
                default: return '.';
            }
            return (color() == Color::WHITE) ? toupper(c) : c;
        }
    private:
        uint8_t m_data; // Bit 0-2: Type, Bit 3: Color (0=white,1=black), Bits 4-7: frei
    };
}


#endif //SCHACHENGINE_PIECE_H