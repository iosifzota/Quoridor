#include "PiecesHandle.h"

PiecesHandle::PiecesHandle(GameType gameType) :
	m_playerCount((int)gameType),
	m_pawnsCount(),
	m_usedPawn(),
	m_wallsPerPlayer(TOTAL_WALLS / (int)gameType)
{
	static_assert((int)GameType::TwoPlayers == 2);
	static_assert((int)GameType::FourPlayers == 4);
}

OptRef<Pawn> PiecesHandle::GetPawn(Direction direction, const Position& pos)
{
	int effectiveIndex = (int)direction;
	if (effectiveIndex < 0 || effectiveIndex > MAX_PLAYERS) // IDEA: interval test function
		return {};

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
