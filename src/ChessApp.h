//
// Created by augus on 06.10.2025.
//

#ifndef SCHACHENGINE_CHESSAPP_H
#define SCHACHENGINE_CHESSAPP_H
#include "GameContainer.h"
#include "core/UIManager.h"

namespace Chess {
    static int TILE_SIZE = 64;
    class ChessApp: public Engine::IGame{
    public:
        ChessApp(Engine::EngineContext &context, Engine::GameContainer &container)
            : IGame(context, container) {
        }

        void update(float dt) override;

        void render() override;

        void onInit() override;

        void onExit() override;
    private:
        UIManager m_ui{m_context};
    };
}


#endif //SCHACHENGINE_CHESSAPP_H