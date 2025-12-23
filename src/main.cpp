
#include <assert.h>

#include "GameContainer.h"
#include "core/ChessBoard.h"
#include "ChessApp.h"
#include "util/Logger.h"


int main() {
    // TODO: Clientsize noch im GC korrigieren
    Engine::GameContainer gc{512+16,512+40,"Schach"};
    gc.createGame<Chess::ChessApp>();
    gc.run();
    // Chess::ChessGame game{};
    // game.getBoard().getOccupied().debugPrint();
    return 0;
}



