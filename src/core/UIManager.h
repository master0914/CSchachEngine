//
// Created by augus on 06.10.2025.
//

#ifndef SCHACHENGINE_UIMANAGER_H
#define SCHACHENGINE_UIMANAGER_H
#pragma once
#include "ChessBoard.h"
#include "EngineContext.h"

namespace Chess {
    class UIManager {
        public:
            UIManager(Engine::EngineContext& context) : m_context(context), m_renderer(*context.renderer2D), m_width(context.window->getm_Width()),
                                                        m_height(context.window->getm_Height()) {
            };
            void render();
            void renderBackground();
            void renderBoard(ChessBoard board);
            void loadImages();
        private:
            Engine::EngineContext& m_context;
            Engine::Renderer_2D& m_renderer;
            // PieceType - 1 = imageID
            std::vector<int> m_imgIDs;
            int m_width, m_height;
    };
}


#endif //SCHACHENGINE_UIMANAGER_H