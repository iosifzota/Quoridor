#include "PiecesHandle.h"
#include "Player.h"

PiecesHandle::PiecesHandle(GameType gameType) :
	m_playerCount(static_cast<int>(gameType)),
	m_pawnsCount(),
	m_usedPawn(),
	m_wallsPerPlayer(TOTAL_WALLS / static_cast<int>(gameType))
{
	static_assert(static_cast<int>(GameType::TwoPlayers) == 2);
	static_assert(static_cast<int>(GameType::ThreePlayers) == 3);
	static_assert(static_cast<int>(GameType::FourPlayers) == 4);
}

OptRef<Pawn> PiecesHandle::GetPawn(Direction direction, const Position& pos)
{
	if (!Piece::validDirection(direction))
		return {};

	int effectiveIndex = (int)direction;

	if (m_pawnsCount < m_playerCount && !m_usedPawn.test(effectiveIndex)) {
		++m_pawnsCount;
		m_usedPawn.set(effectiveIndex);

		return std::ref(m_pawns[effectiveIndex].InitOrigin(direction).InitPosition(pos));
	}

	return {};
}

OptRef<Pawn> PiecesHandle::GetPawn(Direction direction)
{
	return GetPawn(direction, Piece::INVALID_POSITION);
}

// last
OptRef<PlaceableWall> PiecesHandle::GetPlaceableWall(Player& player, const Position& pos, Direction direction)
{
	auto playerOrigin = player.AccessPawn().GetOrigin();
	if (!Piece::validDirection(playerOrigin) ||
		!m_usedPawn.test(static_cast<int>(playerOrigin)) ||
		!player.WallCount()) {
		return {};
	}

	return PlaceableWall::GetInstance(pos, direction);
}

// last
bool PiecesHandle::IsValidPawn(const Pawn& pawn)
{
	if (!Piece::validDirection(pawn.GetOrigin()))
		return false;
	return m_usedPawn.test(static_cast<int>(pawn.GetOrigin()));
}
