#pragma once

#include <utility>
#include <array>
#include <bitset>
using std::array;
using std::bitset;
using Position = std::pair<int, int>;

class Piece {
public:
	// Used by Pawn and Wall
	static const size_t DIRECTION_COUNT = 4; // None excluded
	enum class Direction : char {
		North,
		South,
		East,
		West,
		None = 15
	};

	// constructors
	Piece();
	explicit Piece(const Position&);

	Position& AccessPosition();

// helpers
public:
	// declarations
	using ValidDirectionChecklist = bitset<DIRECTION_COUNT>;

	// procedures
	static void ApplyDirectionMask(Position&, Direction);

	// flags
	static const Position INVALID_POSITION;
	static const Direction INVALID_DIRECTION;
	static bool validDirection(Direction);
	static bool validPosition(const Position&);
protected:
	Position m_position;

private:
	static array<Position, DIRECTION_COUNT> directionMask;
	static void InitDirectionMask();
};
