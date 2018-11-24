#pragma once
#include "Piece.h"

class PlaceableWall:
	public Piece
{
private:
	// one instance
	static PlaceableWall m_instance;
	PlaceableWall(const Position&, Direction);

private:
	Direction m_direction;

public:
	static PlaceableWall& GetInstance(Position, Direction);
};

