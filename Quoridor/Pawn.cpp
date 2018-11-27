#include "Pawn.h"

Pawn::Pawn() :
	Piece(Piece::INVALID_POSITION),
	m_origin(Piece::INVALID_DIRECTION)
{
}
Pawn::Pawn(const Position& p, Direction origin):
	Piece(p),
	m_origin{ origin }
{

}
