#include "PlaceableWall.h"

PlaceableWall::PlaceableWall(Position p, Direction d) :Piece(p), m_direction(d)
{
	/* empty */
}

PlaceableWall & PlaceableWall::GetInstance()
{
	if (m_instance->has_value())
	{
		m_instance->emplace();
	}
	return m_instance->value();
}
