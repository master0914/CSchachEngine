//
// Created by augus on 30.09.2025.
//

#include "ChessBoard.h"

#include <sstream>

namespace Chess {
    ChessBoard::ChessBoard() {
        fromFEN(START_FEN);
        // TEST FENs
        // fromFEN("8/8/8/8/2N2p1P/1p1Np1P1/PPPPPPPP/8 w KQkq - 0 1");
    }

    void ChessBoard::makeMove(Move &move) {
        Square from = static_cast<Square>(move.fromSquare());
        Square to = static_cast<Square>(move.toSquare());
        Piece mover = getPieceAt(from);

        setPieceAt(from, Piece{});
        setPieceAt(to, mover);

        switchColor();
    }

    void ChessBoard::undoMove(Move &move) {
    }

    Piece ChessBoard::getPieceAt(Square square) const{
        if (!(m_occupied.getBit(square))) {
            return Piece{};
        }
        if (m_occupancy[0].getBit(square)) { // WHITE
            if (m_pawns[0].getBit(square)) return Piece(Color::WHITE, SimplePieceType::PAWN);
            if (m_knights[0].getBit(square)) return Piece(Color::WHITE, SimplePieceType::KNIGHT);
            if (m_bishops[0].getBit(square)) return Piece(Color::WHITE, SimplePieceType::BISHOP);
            if (m_rooks[0].getBit(square)) return Piece(Color::WHITE, SimplePieceType::ROOK);
            if (m_queens[0].getBit(square)) return Piece(Color::WHITE, SimplePieceType::QUEEN);
            if (m_kings[0].getBit(square)) return Piece(Color::WHITE, SimplePieceType::KING);
        }
        else { // BLACK
            if (m_pawns[1].getBit(square)) return Piece(Color::BLACK, SimplePieceType::PAWN);
            if (m_knights[1].getBit(square)) return Piece(Color::BLACK, SimplePieceType::KNIGHT);
            if (m_bishops[1].getBit(square)) return Piece(Color::BLACK, SimplePieceType::BISHOP);
            if (m_rooks[1].getBit(square)) return Piece(Color::BLACK, SimplePieceType::ROOK);
            if (m_queens[1].getBit(square)) return Piece(Color::BLACK, SimplePieceType::QUEEN);
            if (m_kings[1].getBit(square)) return Piece(Color::BLACK, SimplePieceType::KING);
        }
        return Piece{};
    }

    Bitboard ChessBoard::getAttackers(Square) {
    }

    Color ChessBoard::getSideToMove() const {
        return m_sideToMove;
    }

    bool ChessBoard::isCheck() const {
    }

    bool ChessBoard::isCheckmate() const {
    }

    bool ChessBoard::isStalemate() const {
    }

    bool ChessBoard::isDraw() const {
    }

    Bitboard ChessBoard::getBitboard(Piece piece) const {
        if (piece.isEmpty()) {
            return Bitboard(0);
        }
        Color color = piece.color();
        int colorIndex = static_cast<int>(color);
        switch (piece.type()) {
            case SimplePieceType::PAWN:
                return m_pawns[colorIndex];
            case SimplePieceType::KNIGHT:
                return m_knights[colorIndex];
            case SimplePieceType::BISHOP:
                return m_bishops[colorIndex];
            case SimplePieceType::ROOK:
                return m_rooks[colorIndex];
            case SimplePieceType::QUEEN:
                return m_queens[colorIndex];
            case SimplePieceType::KING:
                return m_kings[colorIndex];
            default:
                return Bitboard(0);
        }
    }

    Bitboard ChessBoard::getBitboard(SimplePieceType piece, Color color) const {
        if (piece == SimplePieceType::NONE) {
            return Bitboard(0);
        }
        int colorIndex = static_cast<int>(color);
        switch (piece) {
            case SimplePieceType::PAWN:
                return m_pawns[colorIndex];
            case SimplePieceType::KNIGHT:
                return m_knights[colorIndex];
            case SimplePieceType::BISHOP:
                return m_bishops[colorIndex];
            case SimplePieceType::ROOK:
                return m_rooks[colorIndex];
            case SimplePieceType::QUEEN:
                return m_queens[colorIndex];
            case SimplePieceType::KING:
                return m_kings[colorIndex];
            default:
                return Bitboard(0);
        }
    }

    Bitboard ChessBoard::getOccupied() const {
        return m_occupied;
    }
    Bitboard ChessBoard::getOccupancy(Color color) const {
        return m_occupancy[static_cast<int>(color)];
    }

    void ChessBoard::clear() {
        m_pawns[0] = Bitboard{0};
        m_pawns[1] = Bitboard{0};
        m_knights[0] = Bitboard{0};
        m_knights[1] = Bitboard{0};
        m_bishops[0] = Bitboard{0};
        m_bishops[1] = Bitboard{0};
        m_rooks[0] = Bitboard{0};
        m_rooks[1] = Bitboard{0};
        m_queens[0] = Bitboard{0};
        m_queens[1] = Bitboard{0};
        m_kings[0] = Bitboard{0};
        m_kings[1] = Bitboard{0};

        m_occupancy[0] = m_occupancy[1] = m_occupied = Bitboard(0);
        m_boardState.enPassantSquare = Square::INVALID_SQUARE;
        m_boardState.castlingRights = static_cast<CastlingRights>(0);
        m_sideToMove = Color::WHITE;
        m_boardState.halfMoveClock = m_boardState.fullMoveNumber = 0;
        m_boardState.capturedPiece = Piece{};
    }

    void ChessBoard::reset() {
    }

    void ChessBoard::setPieceAt(Square square, Piece piece) {
        Piece oldPiece = getPieceAt(square);
        if(!oldPiece.isEmpty()) {
            switch (oldPiece.type()) {
                case SimplePieceType::PAWN:
                    m_pawns[static_cast<int>(oldPiece.color())].clearBit(square);
                    break;
                case SimplePieceType::KNIGHT:
                    m_knights[static_cast<int>(oldPiece.color())].clearBit(square);
                    break;
                case SimplePieceType::BISHOP:
                    m_bishops[static_cast<int>(oldPiece.color())].clearBit(square);
                    break;
                case SimplePieceType::ROOK:
                    m_rooks[static_cast<int>(oldPiece.color())].clearBit(square);
                    break;
                case SimplePieceType::QUEEN:
                    m_queens[static_cast<int>(oldPiece.color())].clearBit(square);
                    break;
                case SimplePieceType::KING:
                    m_kings[static_cast<int>(oldPiece.color())].clearBit(square);
                    break;
                default:
                    break;
            }
            m_occupancy[static_cast<int>(oldPiece.color())].clearBit(square);
        }
        if(!piece.isEmpty()) {
            switch (piece.type()) {
                case SimplePieceType::PAWN:
                    m_pawns[static_cast<int>(piece.color())].setBit(square);
                    break;
                case SimplePieceType::KNIGHT:
                    m_knights[static_cast<int>(piece.color())].setBit(square);
                    break;
                case SimplePieceType::BISHOP:
                    m_bishops[static_cast<int>(piece.color())].setBit(square);
                    break;
                case SimplePieceType::ROOK:
                    m_rooks[static_cast<int>(piece.color())].setBit(square);
                    break;
                case SimplePieceType::QUEEN:
                    m_queens[static_cast<int>(piece.color())].setBit(square);
                    break;
                case SimplePieceType::KING:
                    m_kings[static_cast<int>(piece.color())].setBit(square);
                    break;
                default:
                    break;
            }

            // Füge zu occupancy hinzu
            m_occupancy[static_cast<int>(piece.color())].setBit(square);
        }
        m_occupied = m_occupancy[0] | m_occupancy[1];
    }
    void ChessBoard::updateOccupancy() {
        // White occupancy
        m_occupancy[0] = m_pawns[0] | m_knights[0] | m_bishops[0] |
                         m_rooks[0] | m_queens[0] | m_kings[0];

        // Black occupancy
        m_occupancy[1] = m_pawns[1] | m_knights[1] | m_bishops[1] |
                         m_rooks[1] | m_queens[1] | m_kings[1];

        m_occupied = m_occupancy[0] | m_occupancy[1];
    }
    void ChessBoard::switchColor() {
        m_sideToMove = getOtherColor(m_sideToMove);
    }

    std::string ChessBoard::toFEN() {
        // danke an deepseek für diesen gut bekannten algoritmus den ich nicht selber an meine implementation anpassen musste :)
        std::string fen;

        // 1. Board Position (Zeilen 8-1)
        for(int rank = 7; rank >= 0; rank--) {
            int emptyCount = 0;

            for(int file = 0; file < 8; file++) {
                auto square = static_cast<Square>(rank * 8 + file);
                Piece piece = getPieceAt(square);

                if(piece.isEmpty()) {
                    emptyCount++;
                } else {
                    if(emptyCount > 0) {
                        fen += std::to_string(emptyCount);
                        emptyCount = 0;
                    }
                    fen += piece.toChar();
                }
            }

            if(emptyCount > 0) {
                fen += std::to_string(emptyCount);
            }
            if(rank > 0) fen += '/';
        }

        // 2. Side to move
        fen += (m_sideToMove == Color::WHITE) ? " w " : " b ";

        // 3. Castling rights
        std::string castling;
        if(m_boardState.castlingRights & WHITE_KINGSIDE) castling += 'K';
        if(m_boardState.castlingRights & WHITE_QUEENSIDE) castling += 'Q';
        if(m_boardState.castlingRights & BLACK_KINGSIDE) castling += 'k';
        if(m_boardState.castlingRights & BLACK_QUEENSIDE) castling += 'q';
        fen += castling.empty() ? "- " : castling + " ";

        // 4. En passant
        fen += (m_boardState.enPassantSquare == Square::INVALID_SQUARE) ? "- " : squareToString(m_boardState.enPassantSquare) + " ";

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
                const Piece piece = Piece{c};
                setPieceAt(square, piece);
                file++;
            }
        }

        // 2. Side to move
        m_sideToMove = (side == "w") ? Color::WHITE : Color::BLACK;

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
            m_boardState.enPassantSquare = Square::INVALID_SQUARE;
        } else {
            m_boardState.enPassantSquare = stringToSquare(enPassant);
        }

        // 5. Move counters
        m_boardState.halfMoveClock = std::stoi(halfMove);
        m_boardState.fullMoveNumber = std::stoi(fullMove);

        // 6. Occupancy Bitboards aktualisieren
        updateOccupancy();
    }
}