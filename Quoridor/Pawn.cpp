#include "Pawn.h"

Pawn::Pawn()
{
}
Pawn::Pawn(const Position& p, Direction origin):
	Piece(p),
	m_origin{ origin }
{

}
