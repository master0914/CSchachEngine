//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_CHESSGAME_H
#define SCHACHENGINE_CHESSGAME_H

#pragma once
#include "ChessBoard.h"
#include "MoveGeneration/MoveGenerator.h"
#include "MoveGeneration/Movelist.h"

namespace Chess {
    class ChessGame {
    public:
        ChessGame() {
            m_board = ChessBoard{};
            updateLegalMoves();
        }
        void makeMove(Move& move);
        void handleLeftClickOnSquare(int square);
        void handleRightClickOnSquare();
        bool isMoveLegal(Move& move);
        Piece getPieceAt(int square);

        // const std::vector<Move>& getLegalMoves() const { return m_legalMoves; }
        // Color getCurrentPlayer() const { return m_currentPlayer; }
        const ChessBoard& getBoard() const { return m_board; }
        const int getSelectedSquare() const {return m_selectedSquare;}
        const Movelist& getMoveList() const {return m_legalMoves;}
    private:
        ChessBoard m_board;
        // in echter boardposition angegeben
        int m_selectedSquare = -1;
        Movelist m_legalMoves;
        MoveGenerator m_moveGenerator;

        void updateLegalMoves();
        bool isValidSelection(int square);
        void switchPlayer();
    };
}


#endif //SCHACHENGINE_CHESSGAME_H