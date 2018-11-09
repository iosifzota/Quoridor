#pragma once
#include "Piece.h"
class Wall :
	public Piece
{
private:
	Direction m_direction;
public:
	Wall();
	Wall(const Position&,Direction);
};

