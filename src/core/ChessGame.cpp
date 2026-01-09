//
// Created by augus on 30.09.2025.
//

#include "ChessGame.h"

namespace Chess {
    void ChessGame::makeMove(Move& move) {
        m_board.makeMove(move);
        updateLegalMoves();
    }

    void ChessGame::handleLeftClickOnSquare(int square) {

        if (m_selectedSquare == -1) {
            if (getPieceAt(square).isEmpty()) return;
            if (isValidSelection(square)) {
                m_selectedSquare = square;
            }
        }else {
            Move move{m_selectedSquare,square};
            if (isMoveLegal(move)) {
                makeMove(move);
                // switchPlayer();
                // updateLegalMoves();
            }
            m_selectedSquare = -1;
        }
    }

    void ChessGame::handleRightClickOnSquare() {
        m_selectedSquare = -1;
    }

    void ChessGame::handleClickOnR() {
        m_board.undoMove();
        updateLegalMoves();
    }

    bool ChessGame::isMoveLegal(Move &move) {
        // @TODO schnellere verarbeitung mit hashing
        for (size_t i = 0; i < m_legalMoves.size(); i++) {
            const Move &lm = m_legalMoves[i];
            if (lm.isSameWithoutFlag(move)) {
                move.setFlags(lm.promotionPiece(),lm.flags(), lm.isCapture());
                return true;
            }
        }
        return false;
    }

    Piece ChessGame::getPieceAt(int square) {
        return m_board.getPieceAt(static_cast<Square>(square));
    }

    void ChessGame::updateLegalMoves() {
        m_legalMoves.clear();
        m_moveGenerator.generateLegalMoves(m_board,m_legalMoves, m_board.getSideToMove());
    }

    bool ChessGame::isValidSelection(int square) {
        // Piece piece = getPieceAt(square);
        // return !piece.isEmpty() && piece.color() == m_currentPlayer;
        return true;
    }

    void ChessGame::switchPlayer() {
        // m_currentPlayer = (m_currentPlayer == Color::WHITE) ?
        //                  Color::BLACK : Color::WHITE;
    }
}
