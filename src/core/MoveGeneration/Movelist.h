//
// Created by augus on 23.12.2025.
//

#ifndef SCHACHENGINE_MOVELIST_H
#define SCHACHENGINE_MOVELIST_H
#include <assert.h>
#include <cstddef>

#include "../Move.h"
#include "../../util/Logger.h"

namespace Chess {
    class Movelist {
    public:
        static constexpr size_t MAX_MOVES = 256;
        Movelist() {
            m_count = 0;
        }
        ~Movelist() {
            for (size_t i = 0; i < m_count; i++) {
                m_moves[i].~Move();
            }
        }

        void add(Move const m) {
            assert(m_count < MAX_MOVES && "Tried to add more than 256 moves to movelist!! sollte nicht passieren");
            // hier verwende ich assert da das einen katasrophalen error geben würde
            m_moves[m_count++] = m;
        }

        size_t size() const { return m_count; }
        bool empty() const { return m_count == 0; }

        Move operator[](size_t i) const{
            assert(i < m_count && "Tried to acces an index out of bounds!! sollte nicht passieren");

            return m_moves[i];
        }

        void clear() { m_count = 0; }
        void pop() {if (m_count > 0) m_count--;}

        void sort(){} // evtl nützlich TODO
        void debugPrint() const{
            for (size_t i = 0; i < m_count; i++) {
                std::cout << m_moves[i] << std::endl;
            }
        }
    private:
        Move m_moves[MAX_MOVES];
        size_t m_count;
    };
}


#endif //SCHACHENGINE_MOVELIST_H