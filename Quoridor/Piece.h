#pragma once

#include <utility>

using Position = std::pair<int, int>;

class Piece {
public:
        // Used by Pawn and Wall
        enum class Direction : char {
                None,
                North,
                South,
                East,
                West
        };

        Piece();
        Piece(const Position&);

        void SetPosition(const Position&);
        const Position& GetPosition() const;

private:
        Position m_position;
};
