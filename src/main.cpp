
#include <assert.h>

#include "GameContainer.h"
#include "core/ChessBoard.h"
#include "ChessApp.h"
#include "util/Logger.h"
#include "tester.h"
#include "core/MoveGeneration/Attacks.h"


int main() {
    Chess::Attacks::init();
    // TODO: Clientsize noch im GC korrigieren
    Engine::GameContainer gc{512,512,"Schach"};
    gc.createGame<Chess::ChessApp>();
    gc.setShowFPS(false);
    gc.run();
    // Chess::testMoveGenerator();
    return 0;
}





