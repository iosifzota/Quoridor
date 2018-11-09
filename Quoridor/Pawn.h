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
Pawn::Pawn()
{

}
Pawn::Pawn(const Position& p, Direction origin) :
	Piece(p),
	m_origin{ origin }
{

}

