#include "Piece.h"

const Position Piece::INVALID_POSITION{ -1, -1 };

Piece::Piece() :
        m_position{-1, -1}
{
        // empty
}
Piece::Piece(const Position& p) :
        m_position{p.first, p.second}
{
        // empty
}

void Piece::SetPosition(const Position& p) {
        m_position = p;
}

const Position& Piece::GetPosition() const {
        return m_position;
}
