#include "PlaceableWall.h"

// one instance
PlaceableWall PlaceableWall::m_instance(Piece::INVALID_POSITION, Piece::INVALID_DIRECTION);

PlaceableWall::PlaceableWall(const Position& pos, Direction direction) :
	Piece(pos), m_direction(direction)
{
	/* empty */
}

void PlaceableWall::SetDirection(Direction direction)
{
	if (!Piece::validDirection(direction))
		throw "invalid direction";
	m_direction = direction;
}

void PlaceableWall::SetPosition(const Position& position)
{
	if (!Piece::validPosition(position))
		throw "invalid position";
	m_position = position;
}

Piece::Direction PlaceableWall::GetDirection() const
{
	return m_direction;
}

const Position& PlaceableWall::GetPosition() const
{
	return m_position;
}

OptRef<PlaceableWall> PlaceableWall::GetInstance(const Position& pos, Direction direction)
{
	if (!Piece::validDirection(direction) || !Piece::validPosition(pos))
		return {};

	m_instance.m_direction = direction;
	m_instance.m_position = pos;
	return m_instance;
}