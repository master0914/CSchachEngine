//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_MOVE_H
#define SCHACHENGINE_MOVE_H

#pragma once
#include <cstdint>

#include "Piece.h"
#include "../util/Helper.h"

namespace Chess {
    class Move {
    public:
        // Konstruktoren
        Move(): m_data(0){}
        // einfacher zug ohne flag
        Move(int from, int to)
        : m_data((from & 0x3F) | ((to & 0x3F) << 6)){}
        // zug mit voller flag
        Move(int from, int to, Flag flag)
        : m_data((from & 0x3F) | ((to & 0x3F) << 6) |
                 ((static_cast<uint16_t>(flag) & 0xF) << 12)) {}
        // promotion ohne capture
        Move(int from, int to, SimplePieceType promotionPiece)
        : Move(from, to) {
            setPromotionFlag(promotionPiece, false);
        }
        // promotion mit capture
        Move(int from, int to, SimplePieceType promotionPiece, bool isCapture)
        : Move(from, to) {
            setPromotionFlag(promotionPiece, isCapture);
        }
        // kompletter konstruktor. vllt unnötig
        Move(int from, int to, SimplePieceType promotion, Flag flag, bool isCapture)
        : Move(from, to) {
            setComplexFlag(promotion, flag, isCapture);
        }

        // Getter
        int fromSquare() const;
        int toSquare() const;
        SimplePieceType promotionPiece() const;
        Flag flags() const;

        // Flags Check
        bool isCapture() const;
        bool isPromotion() const;
        bool isEnPassant() const;
        bool isCastle() const;
        bool isDoublePawnPush() const;

        bool isValid() const;

        // Vergleichsoperatoren für Sorting
        bool operator<(const Move& other) const;
        bool operator==(const Move& other) const;

        std::ostream& operator<<(std::ostream& os) const {
            return os << "MOVE: (" << fromSquare() << ", " << toSquare() << ")" << static_cast<int>(flags());
        }


    private:
        uint16_t m_data;

        // für gute performance nur ein uint16_t mit allen informationen

        // bit layout
        // bits 0-5:   fromSquare (0-63)  2^6
        // bits 6-11:  toSquare (0-63)    2^6
        // bits 12-15: flags (0-F hex)    2^4
        // Flags sind in Helper.h

        void setPromotionFlag(SimplePieceType promotionPiece, bool isCapture) {
            // danke an deepseek
            Flag flag;

            switch (promotionPiece) {
                case SimplePieceType::QUEEN:
                    flag = isCapture ? CAPTURE_PROMO_Q : PROMO_Q;
                    break;
                case SimplePieceType::ROOK:
                    flag = isCapture ? CAPTURE_PROMO_R : PROMO_R;
                    break;
                case SimplePieceType::BISHOP:
                    flag = isCapture ? CAPTURE_PROMO_B : PROMO_B;
                    break;
                case SimplePieceType::KNIGHT:
                    flag = isCapture ? CAPTURE_PROMO_N : PROMO_N;
                    break;
                default:
                    flag = isCapture ? CAPTURE : NORMAL;
                    break;
            }

            m_data |= (static_cast<uint16_t>(flag) << 12);
        }
        void setComplexFlag(SimplePieceType promotion, Flag flag, bool isCapture) {
            // Wenn Promotion, überschreibe Flag
            if (promotion != SimplePieceType::NONE) {
                setPromotionFlag(promotion, isCapture);
            }
            // Wenn keine Promotion, aber Capture mit NORMAL flag
            else if (isCapture && flag == NORMAL) {
                m_data |= (static_cast<uint16_t>(CAPTURE) << 12);
            }
            // Ansonsten übernommener Flag (en passant, castle, etc.)
            else {
                m_data |= (static_cast<uint16_t>(flag) << 12);
            }
        }
    };
}


#endif //SCHACHENGINE_MOVE_H