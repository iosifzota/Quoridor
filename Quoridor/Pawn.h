#pragma once
#include "Piece.h"
class Pawn :
	public Piece
{
public:
	Pawn();
	Pawn(const Position&, Direction origin);

	Pawn& InitOrigin(Direction);
	Pawn& InitPosition(const Position& p);

	Direction GetOrigin() const;
	const Position& GetPosition() const;
private:
	Direction m_origin;
};


