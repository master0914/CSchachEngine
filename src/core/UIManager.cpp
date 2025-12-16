//
// Created by augus on 06.10.2025.
//

#include "UIManager.h"

#include "../ChessApp.h"

namespace Chess {
    void UIManager::render(ChessBoard board) {
        m_renderer.beginFrame();
        renderBackground();
        renderBoard(board);
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

    void UIManager::renderBoard(ChessBoard board) {
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                int screenY = 7 - rank;

                int tilePosX = m_boardOffsetX + (file * 64) + m_pieceOffsetXnY;
                int tilePosY = m_boardOffsetY + (screenY * 64) + m_pieceOffsetXnY;

                Square square = static_cast<Square>(rank * 8 + file);
                PieceType piece = board.getPieceAt(square);

                if (piece == PieceType::NO_PIECE) { continue; }
                m_renderer.drawImage(m_imgIDs.at(static_cast<uint8_t>(piece) - 1),
                                     tilePosX, tilePosY);
            }
        }
    }

    void UIManager::loadImages() {
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhitePawn.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteKnight.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteBishop.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteRook.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteQueen.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackKing.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackPawn.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackKnight.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackBishop.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackRook.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackQueen.png"));
        // m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackKing.png"));
        const std::string spritePath = "../ChessSprites/";

        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhitePawn.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteKnight.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteBishop.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteRook.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteQueen.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "WhiteKing.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackPawn.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackKnight.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackBishop.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackRook.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackQueen.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage(spritePath + "BlackKing.png"));

    }
}
