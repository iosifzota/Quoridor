#pragma once
#include "Piece.h"
class Wall :
	public Piece
{
public:
	Wall();
	Wall(const Position&);
	Direction origin;
};

