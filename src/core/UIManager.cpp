//
// Created by augus on 06.10.2025.
//

#include "UIManager.h"

#include "../ChessApp.h"

namespace Chess {
    void UIManager::render() {
        m_renderer.beginFrame();
        renderBackground();
        m_renderer.drawImage(m_imgIDs[1],0,0);
        m_renderer.present();
    }

    void UIManager::renderBackground() {

    }

    void UIManager::renderBoard(ChessBoard board) {

    }

    void UIManager::loadImages() {
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhitePawn.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteKnight.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteBishop.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteRook.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/WhiteQueen.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackKing.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackPawn.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackKnight.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackBishop.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackRook.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackQueen.png"));
        m_imgIDs.push_back(m_context.renderer2D->loadImage("C:/Users/augus/CLionProjects/CSchachEngine/ChessSprites/BlackKing.png"));

    }
}
