#pragma once

#include <utility>
#include <array>
using std::array;
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

	Position& AccessPosition();

	static void ApplyDirectionMask(Position&, Piece::Direction);
protected:
	Position m_position;

private:
	static array<Position, 5> directionMask;
	void InitDirectionMask(); // FIX ME
};
