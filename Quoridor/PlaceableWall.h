#pragma once
#include "Piece.h"
#include "util_decls.h"

class PlaceableWall:
	public Piece
{
private:
	// one instance
	static PlaceableWall m_instance;
	PlaceableWall(const Position&, Direction);

private:
	Direction m_direction;

public:
	void SetDirection(Direction);
	void SetPosition(const Position&);
	Direction GetDirection() const;
	const Position& GetPosition() const;

	static OptRef<PlaceableWall> GetInstance(const Position&, Direction);
};

