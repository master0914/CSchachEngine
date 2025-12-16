
#include "GameContainer.h"
#include "core/ChessBoard.h"
#include "ChessApp.h"



int main() {
    // TODO: Clientsize noch im GC korrigieren
    Engine::GameContainer gc{512+16,512+40,"Schach"};
    gc.createGame<Chess::ChessApp>();
    gc.run();
    // Chess::ChessBoard board = Chess::ChessBoard{};
    // for (int i = 0; i < 64; i++) {
    //     std::cout << i<<":   "<< pieceToChar(board.getPieceAt(static_cast<Chess::Square>(i))) << std::endl;
    // }
    // for (int i = 1; i <= 12; i++) {
    //     std::cout << i << std::endl;
    //     board.getBitboard(static_cast<Chess::PieceType>(i)).debugPrint();
    // }
    return 0;
}



