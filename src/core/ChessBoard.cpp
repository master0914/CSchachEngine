//
// Created by augus on 30.09.2025.
//

#include "ChessBoard.h"

#include <sstream>

namespace Chess {
    ChessBoard::ChessBoard() {
        fromFEN(START_FEN);
    }

    void ChessBoard::makeMove(Move &move) {
    }

    void ChessBoard::undoMove(Move &move) {
    }

    PieceType ChessBoard::getPieceAt(Square square) {
        if (!(m_occupied.getBit(square))) {
            return PieceType::NO_PIECE;
        }
        for (uint8_t pieceType = static_cast<uint8_t>(PieceType::WHITE_PAWN);
            pieceType <= static_cast<uint8_t>(PieceType::BLACK_KING);
            pieceType++) {
            if (m_bitboards[pieceType - 1].getBit(square)) {
                return static_cast<PieceType>(pieceType);
            }
        }
        return PieceType::NO_PIECE;
    }

    Bitboard ChessBoard::getAttackers(Square) {
    }

    std::string ChessBoard::toFEN() {
        // danke an deepseek für diesen gut bekannten algoritmus den ich nicht selber an meine implementation anpassen musste :)
        std::string fen;

        // 1. Board Position (Zeilen 8-1)
        for(int rank = 7; rank >= 0; rank--) {
            int emptyCount = 0;

            for(int file = 0; file < 8; file++) {
                auto square = static_cast<Square>(rank * 8 + file);
                PieceType piece = getPieceAt(square);

                if(piece == PieceType::NO_PIECE) {
                    emptyCount++;
                } else {
                    if(emptyCount > 0) {
                        fen += std::to_string(emptyCount);
                        emptyCount = 0;
                    }
                    fen += pieceToChar(piece);
                }
            }

            if(emptyCount > 0) {
                fen += std::to_string(emptyCount);
            }
            if(rank > 0) fen += '/';
        }

        // 2. Side to move
        fen += (m_sideToMove == Color::White) ? " w " : " b ";

        // 3. Castling rights
        std::string castling;
        if(m_boardState.castlingRights & WHITE_KINGSIDE) castling += 'K';
        if(m_boardState.castlingRights & WHITE_QUEENSIDE) castling += 'Q';
        if(m_boardState.castlingRights & BLACK_KINGSIDE) castling += 'k';
        if(m_boardState.castlingRights & BLACK_QUEENSIDE) castling += 'q';
        fen += castling.empty() ? "- " : castling + " ";

        // 4. En passant
        fen += (m_boardState.enPassantSquare == INVALID_SQUARE) ? "- " : squareToString(m_boardState.enPassantSquare) + " ";

        // 5. Move counters
        fen += std::to_string(m_boardState.halfMoveClock) + " " + std::to_string(m_boardState.fullMoveNumber);

        return fen;
    }

    void ChessBoard::fromFEN(const std::string& fen) {
        // danke an deepseek für diesen gut bekannten algoritmus den ich nicht selber an meine implementation anpassen musste :)

        // Board zurücksetzen
        clear();

        std::istringstream iss(fen);
        std::string boardPart, side, castling, enPassant, halfMove, fullMove;

        // FEN Teile parsen
        iss >> boardPart >> side >> castling >> enPassant >> halfMove >> fullMove;

        // 1. Board Position parsen
        int rank = 7; // Start bei Rank 8 (oben)
        int file = 0;

        for(char c : boardPart) {
            if(c == '/') {
                // Neue Reihe
                rank--;
                file = 0;
            } else if(isdigit(c)) {
                // Leere Felder überspringen
                file += (c - '0');
            } else {
                // Figur platzieren
                const auto square = static_cast<Square>(rank * 8 + file);
                const PieceType piece = charToPiece(c);
                if (piece == PieceType::BLACK_KING){std::cout<< "TADAAAA" << std::endl;}
                setPieceAt(square, piece);
                file++;
            }
        }

        // 2. Side to move
        m_sideToMove = (side == "w") ? Color::White : Color::Black;

        // 3. Castling rights
        uint8_t castlingTemp = 0;
        if(castling != "-") {
            for(const char c : castling) {
                switch(c) {
                    case 'K': castlingTemp  |= WHITE_KINGSIDE; break;
                    case 'Q': castlingTemp  |= WHITE_QUEENSIDE; break;
                    case 'k': castlingTemp  |= BLACK_KINGSIDE; break;
                    case 'q': castlingTemp  |= BLACK_QUEENSIDE; break;
                    default: break;
                }
            }
        }
        m_boardState.castlingRights = static_cast<CastlingRights>(castlingTemp);

        // 4. En passant square
        if(enPassant == "-") {
            m_boardState.enPassantSquare = INVALID_SQUARE;
        } else {
            m_boardState.enPassantSquare = stringToSquare(enPassant);
        }

        // 5. Move counters
        m_boardState.halfMoveClock = std::stoi(halfMove);
        m_boardState.fullMoveNumber = std::stoi(fullMove);

        // 6. Occupancy Bitboards aktualisieren
        updateOccupancy();
    }

    bool ChessBoard::isCheck() const {
    }

    bool ChessBoard::isCheckmate() const {
    }

    bool ChessBoard::isStalemate() const {
    }

    bool ChessBoard::isDraw() const {
    }

    Bitboard ChessBoard::getBitboard(PieceType pieceType) const {
        return m_bitboards[static_cast<int>(pieceType)-1];
    }

    void ChessBoard::clear() {
        for(auto & m_bitboard : m_bitboards) {
            m_bitboard = Bitboard(0);
        }
        m_occupancy[0] = m_occupancy[1] = m_occupied = Bitboard(0);
        m_boardState.enPassantSquare = INVALID_SQUARE;
        m_boardState.castlingRights = static_cast<CastlingRights>(0);
        m_sideToMove = Color::White;
        m_boardState.halfMoveClock = m_boardState.fullMoveNumber = 0;
        m_boardState.capturedPiece = PieceType::NO_PIECE;
    }

    void ChessBoard::reset() {
    }

    void ChessBoard::setPieceAt(Square square, PieceType piece) {
       // altes muss entfernt werden da in verschiedenen bitboards gespeichert
        PieceType oldPiece = getPieceAt(square);
        if(oldPiece != PieceType::NO_PIECE) {
            int oldIndex = static_cast<int>(oldPiece) - 1;
            m_bitboards[oldIndex].clearBit(square);

            Color oldColor = getPieceColor(oldPiece);
            m_occupancy[static_cast<int>(oldColor)].clearBit(square);
        }
        if(piece != PieceType::NO_PIECE) {
            int newIndex = static_cast<int>(piece) - 1;
            m_bitboards[newIndex].setBit(square);

            Color newColor = getPieceColor(piece);
            m_occupancy[static_cast<int>(newColor)].setBit(square);
        }
        m_occupied = m_occupancy[0] | m_occupancy[1];
    }
    void ChessBoard::updateOccupancy() {
        m_occupancy[0] = Bitboard(0); // w
        m_occupancy[1] = Bitboard(0); // b

        for(int i = 0; i < 6; i++) {
            m_occupancy[0] = m_occupancy[0] | m_bitboards[i];     // w
            m_occupancy[1] = m_occupancy[1] | m_bitboards[i + 6]; // b
        }

        m_occupied = m_occupancy[0] | m_occupancy[1];
    }
}