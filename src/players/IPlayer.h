//
// Created by augus on 30.09.2025.
//

#ifndef SCHACHENGINE_IPLAYER_H
#define SCHACHENGINE_IPLAYER_H
#include "../core/Move.h"
#include "../core/ChessGame.h"

#endif //SCHACHENGINE_IPLAYER_H

namespace Chess {
    class IPlayer {
        public:
        IPlayer(bool isWhite, bool isHuman): m_isWhite(isWhite), m_isHuman(isHuman) {}
        virtual ~IPlayer() = default;

        virtual Move getMove(ChessGame&);
        bool isHuman() const{return m_isHuman;}
        bool isWhite() const{return m_isWhite;}
    private:
        bool m_isHuman;
        bool m_isWhite;
    };
}