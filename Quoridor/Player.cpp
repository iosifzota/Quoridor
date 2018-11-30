#include "Player.h"

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

size_t Player::WallCount()
{
	return m_wallCount;
}
