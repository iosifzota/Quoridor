#pragma once
#include "Piece.h"
#include <optional>
using std::optional;

class PlaceableWall:
	public Piece
{
private:
	static optional<PlaceableWall> m_instance;
	
	PlaceableWall() = default;
	PlaceableWall(Position p, Direction d);
	
	Direction m_direction;

public:
	static PlaceableWall& GetInstance();
};

