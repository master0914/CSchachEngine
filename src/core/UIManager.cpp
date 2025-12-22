//
// Created by augus on 06.10.2025.
//

#include "UIManager.h"

#include "../ChessApp.h"

namespace Chess {
    void UIManager::update() {
        Engine::vec2 mouseScreenPos = m_context.input->getMousePosition();
        bool isMouseOverBoard =
        mouseScreenPos.x >= m_boardOffsetX &&
        mouseScreenPos.x < m_boardOffsetX + 512 && // 8*64
        mouseScreenPos.y >= m_boardOffsetY &&
        mouseScreenPos.y < m_boardOffsetY + 512;

        int boardPosX = static_cast<int>((mouseScreenPos.x - m_boardOffsetX)/64);
        int boardPosY = static_cast<int>((mouseScreenPos.y - m_boardOffsetY)/64);

        if (boardPosX < 0 || boardPosX >= 8 || boardPosY < 0 || boardPosY >= 8) {
            return;
        }

        int boardIndex = boardPosY * 8 + boardPosX;
        if (isMouseOverBoard) {
            if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
                m_game.handleClickOnSquare(boardIndex);
            }
        }
    }

    void UIManager::render() {
        m_renderer.beginFrame();
        renderBackground();
        renderBoard();
        m_renderer.present();
    }

    void UIManager::renderBackground() {
        // m_renderer.fillRectangle(m_boardOffsetX,m_boardOffsetY,m_boardWidth,m_boardHeight,m_colorWhite);
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                int tilePosX = m_boardOffsetX + (row * 64);
                int tilePosY = m_boardOffsetY + (col * 64);
                uint32_t color = (((col + row) % 2) == 0) ? m_colorWhite : m_colorBlack;
                m_renderer.fillRectangle(tilePosX, tilePosY, m_squareSize,m_squareSize, color);
            }
        }
    }

    void UIManager::renderBoard() {
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                int screenY = 7 - rank;

                int tilePosX = m_boardOffsetX + (file * 64) + m_pieceOffsetXnY;
                int tilePosY = m_boardOffsetY + (screenY * 64) + m_pieceOffsetXnY;

                Square square = static_cast<Square>(rank * 8 + file);
                Piece piece = m_game.getBoard().getPieceAt(square);

                if (piece.isEmpty()) { continue; }
                int colorIdx = static_cast<int>(piece.color());
                int typeIdx = static_cast<int>(piece.type()) - 1; // PAWN=1 -> 0
                int textureIndex = colorIdx * 6 + typeIdx;

                m_renderer.drawImage(m_imgIDs.at(textureIndex),
                                     tilePosX, tilePosY);
            }
        }
    }

    void UIManager::loadImages() {

        const std::string spritePath = "../ChessSprites/";

        std::string pieceNames[2][6] = {
            {"WhitePawn", "WhiteKnight", "WhiteBishop", "WhiteRook", "WhiteQueen", "WhiteKing"},
            {"BlackPawn", "BlackKnight", "BlackBishop", "BlackRook", "BlackQueen", "BlackKing"}
        };

        for (int color = 0; color < 2; color++) {
            for (int type = 0; type < 6; type++) {
                std::string filename = spritePath + pieceNames[color][type] + ".png";
                m_imgIDs.push_back(m_context.renderer2D->loadImage(filename));
            }
        }

        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhitePawn.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteKnight.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteBishop.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteRook.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteQueen.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteKing.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackPawn.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackKnight.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackBishop.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackRook.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackQueen.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackKing.png"));

    }
}
