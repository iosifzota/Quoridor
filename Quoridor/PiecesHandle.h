#pragma once

#include "Pawn.h"
#include "util_decls.h"
#include "PlaceableWall.h"
#include <array>
using std::array;
using std::size_t;

// forward decl
class Player;

using Direction = Piece::Direction;

class PiecesHandle
{
public:
	PiecesHandle(GameType); // from util_decls.h

	OptRef<Pawn> GetPawn(Direction direction);
	OptRef<Pawn> GetPawn(Direction direction, const Position&);

	OptRef<PlaceableWall> GetPlaceableWall(Player&, const Position&, Direction);
	const size_t m_wallsPerPlayer;

	bool IsValidPawn(const Pawn&);

private:
	const size_t m_playerCount;
	static const size_t TOTAL_WALLS = 16;
	static const size_t MAX_PLAYERS = 4;
	array<Pawn, MAX_PLAYERS> m_pawns;

	// helpers
	size_t m_pawnsCount;
	Piece::DirectionChecklist m_usedPawn;
};
