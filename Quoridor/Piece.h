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
		static const Position INVALID_POSITION;

        Piece();
        explicit Piece(const Position&);

        void SetPosition(const Position&);
        const Position& GetPosition() const;

protected:
        Position m_position;
};
