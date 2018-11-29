#include "Pawn.h"

Pawn::Pawn() :
	Piece(Piece::INVALID_POSITION),
	m_origin(Piece::INVALID_DIRECTION)
{
}
Pawn::Pawn(const Position& p, Direction origin):
	Piece(p),
	m_origin{ origin }
{

}

Pawn& Pawn::InitOrigin(Direction direction)
{
	if (validDirection(direction))
		m_origin = direction;
	return *this;
}

Pawn& Pawn::InitPosition(const Position& p)
{
	if (validPosition(m_position))
		m_position = p;
	return *this;
}

Piece::Direction Pawn::GetOrigin() const
{
	return m_origin;
}

const Position& Pawn::GetPosition() const
{
	return m_position;
}