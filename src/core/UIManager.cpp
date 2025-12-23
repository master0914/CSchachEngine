//
// Created by augus on 06.10.2025.
//

#include "UIManager.h"

#include "../ChessApp.h"
#include "../util/Logger.h"

namespace Chess {
    void UIManager::update() const {
        if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_RIGHT)) {
            m_game.handleRightClickOnSquare();
            return;
        }

        Engine::vec2 mouseScreenPos = m_context.input->getMousePosition();
        const bool isMouseOverBoard =
        mouseScreenPos.x >= m_boardOffsetX &&
        mouseScreenPos.x < m_boardOffsetX + 512 &&
        mouseScreenPos.y >= m_boardOffsetY &&
        mouseScreenPos.y < m_boardOffsetY + 512;


        if (isMouseOverBoard) {
            if (m_context.input->isMouseButtonJustPressed(Engine::KeyCode::MOUSE_LEFT)) {
                int boardPosX = static_cast<int>((mouseScreenPos.x - m_boardOffsetX)/64);
                int boardPosY = static_cast<int>((mouseScreenPos.y - m_boardOffsetY)/64);

                if (boardPosX < 0 || boardPosX >= 8 || boardPosY < 0 || boardPosY >= 8) {
                    LOG_ERROR("OH OH! Ein klick wurde außerhalb des boards gemacht????????");
                    return; // sollte nie passieren
                }
                // boardPosY wird für das angezeigte board berechnet muss noch gespiegelt werden
                // int invertedBoardPosY = 7 - boardPosY;
                // int boardIndex = invertedBoardPosY * 8 + boardPosX;
                int boardIndex = uiToBoardIndex(boardPosX, boardPosY);
                m_game.handleLeftClickOnSquare(boardIndex);
            }
        }
    }

    void UIManager::render() const {
        m_renderer.beginFrame();
        renderBackground();
        renderBoard();
        renderHeldPiece();
        m_renderer.present();
    }

    void UIManager::renderBackground() const {
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

    void UIManager::renderBoard() const {
        for (int rank = 0; rank < 8; rank++) {
            for (int file = 0; file < 8; file++) {
                if (XYtoBoardIndex(rank,file) == m_game.getSelectedSquare()) {
                    continue;
                }
                int screenY = 7 - rank;

                int tilePosX = m_boardOffsetX + (file * 64) + m_pieceOffsetXnY;
                int tilePosY = m_boardOffsetY + (screenY * 64) + m_pieceOffsetXnY;

                Square square = static_cast<Square>(XYtoBoardIndex(rank, file));

                Piece piece = m_game.getBoard().getPieceAt(square);

                renderPiece(piece, tilePosX, tilePosY);
            }
        }
    }

    void UIManager::renderHeldPiece() const {
        int selectedSquare = m_game.getSelectedSquare();
        if (selectedSquare != -1) {
            const Piece piece = m_game.getBoard().getPieceAt(static_cast<Square>(selectedSquare));
            const Engine::vec2 pos = m_context.input->getMousePosition();
            renderPiece(piece, pos.x - m_heldPieceOffsetXnY, pos.y - m_heldPieceOffsetXnY);
        }
    }

    void UIManager::renderPiece(Piece piece, int x, int y) const {
        if (piece.isEmpty()) { return;}
        int colorIdx = static_cast<int>(piece.color());
        int typeIdx = static_cast<int>(piece.type()) - 1; // PAWN=1 -> 0
        int textureIndex = colorIdx * 6 + typeIdx;

        m_renderer.drawImage(m_imgIDs.at(textureIndex),
                             x, y);
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
