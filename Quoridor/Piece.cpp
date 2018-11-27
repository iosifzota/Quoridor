#include "Piece.h"

const Position Piece::INVALID_POSITION{ -1, -1 };
array<Position, 5> Piece::directionMask{};

Piece::Piece() :
        m_position{-1, -1}
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

void Piece::ApplyDirectionMask(Position& pos, Piece::Direction direction)
{
	addPosition(pos, directionMask[(int)direction]);
}

// FIX ME
void Piece::InitDirectionMask()
{
	static bool initalized = false;

	if (initalized) return;

	directionMask.at((int)Direction::North).first = -1;
	directionMask.at((int)Direction::South).first = +1;
	directionMask.at((int)Direction::East).second = -1;
	directionMask.at((int)Direction::None).second = +1;
	initalized = true;
}
