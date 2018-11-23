#pragma once
#include "Piece.h"
#include <optional>
using std::optional;

class PlaceableWall:
	public Piece
{
private:
	static optional<PlaceableWall> m_instance;
	
	Direction m_direction;

public:
	PlaceableWall() = default;
	PlaceableWall(Position p, Direction d);

	static PlaceableWall& GetInstance();
};

