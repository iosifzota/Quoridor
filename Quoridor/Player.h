#pragma once

#include "PiecesHandle.h"

class Board;

class Player
{
private:
	Player(Pawn&, PiecesHandle& ph);

public:
	static optional<Player> MakePlayer(Direction, PiecesHandle&); // last in this file

	Pawn& AccessPawn();
	size_t WallCount() const;

	OptRef<PlaceableWall> PickWall(const Position&, Direction, PiecesHandle&);
	void PlaceWall(Board&, PlaceableWall&, function<void(bool)>);
private:
	size_t m_wallCount;
	ref_wrapper<Pawn> m_pawn;
};