//
// Created by augus on 02.01.2026.
//

#ifndef SCHACHENGINE_TESTER_H
#define SCHACHENGINE_TESTER_H
#include "core/MoveGenerator.h"

#endif //SCHACHENGINE_TESTER_H

namespace Chess {
    inline std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    inline std::string knightTest = "N6N/5b2/4b3/8/3N4/8/1N6/7N w - - 0 1";
    inline void testMoveGenerator() {
        // int sq = 17;
        // std::cout << rankOf(sq) << " " << fileOf(sq) << "\n";
        ChessBoard board;
        board.fromFEN(knightTest);
        MoveGenerator moves;
        Movelist movesList;
        moves.generateLegalMoves(board,movesList,Color::WHITE);
        movesList.debugPrint();
    }

}