//
// Created by augus on 23.12.2025.
//

#ifndef SCHACHENGINE_MOVEGENERATOR_H
#define SCHACHENGINE_MOVEGENERATOR_H
#include "../ChessBoard.h"
#include "Movelist.h"

namespace Chess {
    class MoveGenerator {
    public:
        MoveGenerator() {

        }
        void generateLegalMoves(const ChessBoard& board,
                                   Movelist& moveList,
                                   Color sideToMove);
        void generatePseudoLegalMoves(const ChessBoard& board,
                                         Movelist& moveList,
                                         Color sideToMove);

        // nur zum testen
        void generateMovesFromSquare(const ChessBoard& board,
                                        Movelist& moveList,
                                        Square square,
                                        Color sideToMove);
    private:
        // bauern
        void generatePawnMoves(const ChessBoard& board,
                                  Movelist& moveList,
                                  Color color);

        void generatePawnNonCaptures(const ChessBoard& board,
                                            Movelist& moveList,
                                            Color color);

        void generatePawnCaptures(const ChessBoard& board,
                                         Movelist& moveList,
                                         Color color);

        void generatePawnPromotions(const ChessBoard& board,
                                           Movelist& moveList,
                                           Square from, Square to,
                                           bool isCapture);
        void generateEnPassantMoves(const ChessBoard& board,
                                       Movelist& moveList,
                                       Color color);
        // springer
        void generateKnightMoves(const ChessBoard& board,
                                    Movelist& moveList,
                                    Color color);
        // läufer
        void generateBishopMoves(const ChessBoard& board,
                                        Movelist& moveList,
                                        Color color);
        // türme
        void generateRookMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);

        // damen
        void generateQueenMoves(const ChessBoard& board,
                                       Movelist& moveList,
                                       Color color);

        // könige
        void generateKingMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);
        // rochade
        void generateCastlingMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);

        // HELPER-----------------------------------
        // TODO: ATTACK CHECK und precalculated attack tables
        void isSquareAttacked(const ChessBoard&, Square square, Color color);

        // filtert die illegalen aus der pseudolegal movelist
        void filterIllegalMoves(const ChessBoard& board,
                                   Movelist& moveList,
                                   Color sideToMove);
        bool canCastleKingside(const ChessBoard& board, Color color);
        bool canCastleQueenside(const ChessBoard& board, Color color);

        Color oppositeColor(Color color) {
            return (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
        }
        // Direction lookup-----------------------------
        // r is rank
        // f is file


        // Attack Table---------------------------------


    };
}

#endif //SCHACHENGINE_MOVEGENERATOR_H