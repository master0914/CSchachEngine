//
// Created by augus on 06.10.2025.
//

#include "ChessApp.h"

#include "core/ChessBoard.h"

namespace Chess {
    void ChessApp::update(float dt) {
    }

    void ChessApp::render() {
        m_ui.render();
    }

    void ChessApp::onInit() {
        m_ui.loadImages();
    }

    void ChessApp::onExit() {
    }
}
