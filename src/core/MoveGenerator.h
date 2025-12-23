//
// Created by augus on 23.12.2025.
//

#ifndef SCHACHENGINE_MOVEGENERATOR_H
#define SCHACHENGINE_MOVEGENERATOR_H
#include "ChessBoard.h"
#include "Movelist.h"

namespace Chess {
    class MoveGenerator {
    public:
        MoveGenerator();
        static void generateLegalMoves(const ChessBoard& board,
                                   Movelist& moveList,
                                   Color sideToMove);
        static void generatePseudoLegalMoves(const ChessBoard& board,
                                         Movelist& moveList,
                                         Color sideToMove);

        // nur zum testen
        static void generateMovesFromSquare(const ChessBoard& board,
                                        Movelist& moveList,
                                        Square square,
                                        Color sideToMove);
    private:
        // bauern
        static void generatePawnMoves(const ChessBoard& board,
                                  Movelist& moveList,
                                  Color color);

        static void generatePawnNonCaptures(const ChessBoard& board,
                                            Movelist& moveList,
                                            Color color);

        static void generatePawnCaptures(const ChessBoard& board,
                                         Movelist& moveList,
                                         Color color);

        static void generatePawnPromotions(const ChessBoard& board,
                                           Movelist& moveList,
                                           Square from, Square to,
                                           bool isCapture);
        static void generateEnPassantMoves(const ChessBoard& board,
                                       Movelist& moveList,
                                       Color color);
        // springer
        static void generateKnightMoves(const ChessBoard& board,
                                    Movelist& moveList,
                                    Color color);
        // läufer
        static void generateBishopMoves(const ChessBoard& board,
                                        Movelist& moveList,
                                        Color color);
        // türme
        static void generateRookMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);

        // damen
        static void generateQueenMoves(const ChessBoard& board,
                                       Movelist& moveList,
                                       Color color);

        // könige
        static void generateKingMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);
        // rochade
        static void generateCastlingMoves(const ChessBoard& board,
                                      Movelist& moveList,
                                      Color color);

        // HELPER--------------------------
        // TODO: ATTACK CHECK und precalculated attack tables
        static void isSquareAttacked(const ChessBoard&, Square square, Color color);

        // filtert die illegalen aus der pseudolegal movelist
        static void filterIllegalMoves(const ChessBoard& board,
                                   Movelist& moveList,
                                   Color sideToMove);
        static bool canCastleKingside(const ChessBoard& board, Color color);
        static bool canCastleQueenside(const ChessBoard& board, Color color);

        static Color oppositeColor(Color color) {
            return (color == Color::WHITE) ? Color::BLACK : Color::WHITE;
        }
    };
}

#endif //SCHACHENGINE_MOVEGENERATOR_H