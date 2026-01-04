//
// Created by augus on 30.09.2025.
//

#include "ChessBoard.h"

#include <sstream>

#include "../util/Logger.h"

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

        m_lastMove.from = from;
        m_lastMove.to = to;
        m_lastMove.movedPiece = mover;
        m_lastMove.capturedPiece = getPieceAt(to);

        // ja mir ist klar bitboard operations sind hässlich aber es ist schneller als setPieceAt
        // mover von from entfernen
        m_bitboards[toInt(mover.color())][toInt(mover.type()) - 1].clearBit(from);
        m_occupancy[toInt(mover.color())].clearBit(from);

        // falls ein piece gecaptured wurde entfernen
        if (!m_lastMove.capturedPiece.isEmpty()) {
            m_bitboards[toInt(m_lastMove.capturedPiece.color())][toInt(m_lastMove.capturedPiece.type()) - 1].clearBit(to);
            m_occupancy[toInt(m_lastMove.capturedPiece.color())].clearBit(to);
        }
        // mover zu to hinzufügen
        m_bitboards[toInt(mover.color())][toInt(mover.type()) - 1].setBit(to);
        m_occupancy[toInt(mover.color())].setBit(to);

        // occupancy updaten
        m_occupied = m_occupancy[0] | m_occupancy[1];
        // clearSquare(from, mover);
        // setPieceAt(to, mover);

        switchColor();
    }

    // WICHTIG!! keine move history! soll nur direkt nach makeMove aufgerufen werden!!
    void ChessBoard::undoMove() {
        // TODO boardstate undoen
        Piece movedPiece = m_lastMove.movedPiece;

        // movedPiece von to entfernen
        m_bitboards[toInt(movedPiece.color())][toInt(movedPiece.type()) - 1].clearBit(m_lastMove.to);
        m_occupancy[toInt(movedPiece.color())].clearBit(m_lastMove.to);

        // movedPiece zu from hinzufügen
        m_bitboards[toInt(movedPiece.color())][toInt(movedPiece.type()) - 1].setBit(m_lastMove.from);
        m_occupancy[toInt(movedPiece.color())].setBit(m_lastMove.from);

        // captured Piece wiederherstellen
        if (!m_lastMove.capturedPiece.isEmpty()) {
            m_bitboards[toInt(m_lastMove.capturedPiece.color())][toInt(m_lastMove.capturedPiece.type()) - 1].setBit(m_lastMove.to);
            m_occupancy[toInt(m_lastMove.capturedPiece.color())].setBit(m_lastMove.to);
        }

        // occupancy updaten
        m_occupied = m_occupancy[0] | m_occupancy[1];

        switchColor();
    }

    // diese methoden sind nicht so schnell wie sie seien könnten aber werden nur in UI code etc verwendet deshalb egal
    // ja ich weiß sie wird in makeMove 2mal aufgerufen aber damit bin ich noch fine. @TODO nicht mehr in makemove verwenden
    Piece ChessBoard::getPieceAt(Square square) const{
        if (!(m_occupied.getBit(square))) {
            return Piece{};
        }
        if (m_occupancy[0].getBit(square)) { // WHITE
            for (int p = 0; p < 6; ++p) {
                if (m_bitboards[0][p].getBit(square)) {
                    return Piece(Color::WHITE, static_cast<SimplePieceType>(p + 1));
                }
            }
        }
        else if (m_occupancy[1].getBit(square)){ // BLACK
            for (int p = 0; p < 6; ++p) {
                if (m_bitboards[1][p].getBit(square)) {
                    return Piece(Color::BLACK, static_cast<SimplePieceType>(p + 1));
                }
            }
        }
        return Piece{};
    }
    void ChessBoard::setPieceAt(Square square, Piece piece) {
        Piece oldPiece = getPieceAt(square);
        if(!oldPiece.isEmpty()) {
            m_bitboards[toInt(oldPiece.color())][(toInt(oldPiece.type()) - 1)].clearBit(square);

            // Füge zu occupancy hinzu
            m_occupancy[toInt(oldPiece.color())].clearBit(square);
        }
        if(!piece.isEmpty()) {
            m_bitboards[toInt(piece.color())][(toInt(piece.type()) - 1)].setBit(square);

            // Füge zu occupancy hinzu
            m_occupancy[toInt(piece.color())].setBit(square);
        }
        m_occupied = m_occupancy[0] | m_occupancy[1];
    }

    void ChessBoard::updateOccupancy() {
        // White occupancy
        m_occupancy[0] = m_bitboards[0][0] | m_bitboards[0][1] | m_bitboards[0][2] |
                         m_bitboards[0][3] | m_bitboards[0][4] | m_bitboards[0][5];

        // Black occupancy
        m_occupancy[1] = m_bitboards[1][0] | m_bitboards[1][1] | m_bitboards[1][2] |
                         m_bitboards[1][3] | m_bitboards[1][4] | m_bitboards[1][5];

        m_occupied = m_occupancy[0] | m_occupancy[1];
    }
    void ChessBoard::switchColor() {
        m_sideToMove = getOtherColor(m_sideToMove);
    }
    void ChessBoard::clear() {
        for (int c = 0; c < 2; ++c) {
            for (int p = 0; p < 6; ++p) {
                m_bitboards[c][p] = Bitboard(0);
            }
        }

        m_occupancy[0] = m_occupancy[1] = m_occupied = Bitboard(0);
        m_boardState.enPassantSquare = Square::INVALID_SQUARE;
        m_boardState.castlingRights = static_cast<CastlingRights>(0);
        m_sideToMove = Color::WHITE;
        m_boardState.halfMoveClock = m_boardState.fullMoveNumber = 0;
        m_lastMove = LastMoveInfo();
    }
    void ChessBoard::reset() {
    }

    Bitboard ChessBoard::getBitboard(Piece piece) const {
        if (piece.isEmpty()) {
            LOG_WARN("Tried to access bitboard of piece NONE!!");
            return Bitboard(0);
        }

        int colorIndex = static_cast<int>(piece.color());
        // sollte hier ok sein da NONE = 0 schon ausgeschlossen wurde
        return m_bitboards[colorIndex][toInt(piece.type()) - 1];
    }

    Bitboard ChessBoard::getBitboard(SimplePieceType piece, Color color) const {
        if (piece == SimplePieceType::NONE) {
            LOG_WARN("Tried to access bitboard of piece NONE!!");
            return Bitboard(0);
        }
        int colorIndex = static_cast<int>(color);
        // sollte hier ok sein da NONE = 0 schon ausgeschlossen wurde
        return m_bitboards[colorIndex][toInt(piece) - 1];
    }

    Bitboard ChessBoard::getOccupied() const {
        return m_occupied;
    }
    Bitboard ChessBoard::getOccupancy(Color color) const {
        return m_occupancy[static_cast<int>(color)];
    }

    Bitboard ChessBoard::getAttackers(Square) {
        return Bitboard{};
    }

    Color ChessBoard::getSideToMove() const {
        return m_sideToMove;
    }

    bool ChessBoard::isCheck() const {
        return false;
    }

    bool ChessBoard::isCheckmate() const {
        return false;
    }

    bool ChessBoard::isStalemate() const {
        return false;
    }

    bool ChessBoard::isDraw() const {
        return false;
    }

    void ChessBoard::debugPrint() const {
        for (int i = 0; i < 64; i++) {
            std::cout << getPieceAt(static_cast<Square>(i)).toChar() << " ";
            if (i % 8 == 7) std::cout << std::endl;
        }
        std::cout << "For White Pieces" << std::endl;
        for (int i = 0; i < 6; i++) {
            std::cout << "for piece: " << Piece{Color::WHITE,static_cast<SimplePieceType>(i + 1)}.toChar() << std::endl;
            m_bitboards[0][i].debugPrint();
        }
        std::cout << "For Black Pieces" << std::endl;
        for (int i = 0; i < 6; i++) {
            std::cout << "for piece: " << Piece{Color::BLACK,static_cast<SimplePieceType>(i + 1)}.toChar() << std::endl;
            m_bitboards[1][i].debugPrint();
        }
        std::cout << std::endl;
        std::cout << std::endl;
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
