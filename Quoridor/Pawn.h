#pragma once
#include "Piece.h"
class Pawn :
	public Piece

{
public:
	Pawn();
	Pawn(const Position&, Direction origin);
	Direction origin;
private:
	Direction m_origin;
};


