#include "Piece.h"

const Position Piece::INVALID_POSITION{ -1, -1 };
const Piece::Direction Piece::INVALID_DIRECTION = Piece::Direction::None;
array<Position, Piece::DIRECTION_COUNT> Piece::directionMask{};

Piece::Piece() :
        m_position{INVALID_POSITION}
{
	InitDirectionMask();
}
Piece::Piece(const Position& p) :
        m_position{p.first, p.second}
{
	InitDirectionMask();
}

Position& Piece::AccessPosition() {
        return m_position;
}

static void addPosition(Position& dest, const Position& other)
{
	auto&[x_dest, y_dest] = dest;
	auto&[x_other, y_other] = other;
	x_dest += x_other;
	y_dest += y_other;
}

void Piece::ApplyDirectionMask(Position& pos, Direction direction)
{
	addPosition(pos, directionMask[(int)direction]);
}

bool Piece::validDirection(Direction direction)
{
	return (direction != INVALID_DIRECTION) ? true : false;
}

bool Piece::validPosition(const Position& pos)
{
	return (pos != INVALID_POSITION) ? true : false;
}

// FIX ME
void Piece::InitDirectionMask()
{
	static bool initalized = false;

	if (initalized) return;

	directionMask.at((int)Direction::North).first = -1;
	directionMask.at((int)Direction::South).first = +1;
	directionMask.at((int)Direction::West).second = -1;
	directionMask.at((int)Direction::East).second = +1;
	initalized = true;
}

// dead code
static void assertDirectionAsIndecies()
{
	static_assert((int)Piece::Direction::North == 0);
	static_assert((int)Piece::Direction::South == 1);
	static_assert((int)Piece::Direction::East == 2);
	static_assert((int)Piece::Direction::West == 3);
	static_assert((int)Piece::Direction::None == 15);
}