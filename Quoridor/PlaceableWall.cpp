#include "PlaceableWall.h"

// one instance
PlaceableWall PlaceableWall::m_instance(Piece::INVALID_POSITION, Piece::Direction::None);

PlaceableWall::PlaceableWall(const Position& pos, Direction direction) :
	Piece(pos), m_direction(direction)
{
	/* empty */
}

PlaceableWall& PlaceableWall::GetInstance(Position pos, Direction direction)
{
	m_instance.m_direction = direction;
	m_instance.m_position = pos;
	return m_instance;
}
