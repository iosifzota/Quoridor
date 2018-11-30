#include "Player.h"
#include "Board.h"

Player::Player(Pawn& pawn, PiecesHandle& ph) :
	m_pawn{pawn},
	m_wallCount{ph.m_wallsPerPlayer}
{
	if (!ph.IsValidPawn(pawn))
		throw "error";
}

// last in this file
optional<Player> Player::MakePlayer(Direction direction, PiecesHandle& ph)
{
	auto pawnOptRef = ph.GetPawn(direction);

	if (pawnOptRef.has_value()) {
		Pawn& pawn = pawnOptRef.value().get();
		return Player{ pawn, ph };
	}

	return {};
}

Pawn& Player::AccessPawn()
{
	return m_pawn;
}

size_t Player::WallCount() const
{
	return m_wallCount;
}

OptRef<PlaceableWall> Player::PickWall(const Position& position, Direction direction, PiecesHandle& ph)
{
	return ph.GetPlaceableWall(*this, position, direction);
}

void Player::PlaceWall(Board& board, PlaceableWall& placeableWall, function<void(bool)> proc)
{
	board.PlaceWall(*this, placeableWall, proc);
}
