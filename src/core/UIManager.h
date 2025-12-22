//
// Created by augus on 06.10.2025.
//

#ifndef SCHACHENGINE_UIMANAGER_H
#define SCHACHENGINE_UIMANAGER_H
#pragma once
#include "ChessBoard.h"
#include "ChessGame.h"
#include "EngineContext.h"

namespace Chess {
    class UIManager {
        public:
            UIManager(Engine::EngineContext& context, ChessGame& game) : m_context(context), m_renderer(*context.renderer2D), m_width(context.window->getm_Width()),
                                                        m_height(context.window->getm_Height()), m_game(game) {
            };
            void update();
            void render();
            void renderBackground();
            void renderBoard();
            void loadImages();
        private:
            Engine::EngineContext& m_context;
            Engine::Renderer_2D& m_renderer;
            ChessGame& m_game;
            // Inputstuff -------------------
            int m_selectedSquare;
            bool m_isPieceSelected;
            // Renderstuff -----------------
            // PieceType - 1 = imageID
            std::vector<int> m_imgIDs;
            int m_width, m_height;
            // board parameter
            int m_boardOffsetX = 0;
            int m_boardOffsetY = 0;
            int m_boardWidth = 512;  // muss so bleiben
            int m_boardHeight = 512; // muss so bleiben
            int m_squareSize = 64;
            uint32_t m_colorBlack = 0xff5b3a29;
            uint32_t m_colorWhite = 0xffd7b891;
            int m_pieceOffsetXnY = 10; // die sprites sind alle 45x45 also müssen sie im feld zentriert werden
    };
}


#endif //SCHACHENGINE_UIMANAGER_H