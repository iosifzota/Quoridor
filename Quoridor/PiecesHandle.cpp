#include "PiecesHandle.h"

PiecesHandle::PiecesHandle(size_t playerCount) :
	m_playerCount(playerCount),
	m_pawnsCount(),
	m_usedPawn(),
	m_wallsPerPlayer(TOTAL_WALLS / playerCount)
{
	//m_playerCount < MAX_PLAYERS && m_playerCount > 1
}
 
optional<ref_wrapper<Pawn>> PiecesHandle::GetPawn(Direction direction)
{
	int effectiveIndex = (int)direction;
	if (effectiveIndex < 0 || effectiveIndex > MAX_PLAYERS)
		return {};
	
	if (m_pawnsCount < m_playerCount && !m_usedPawn.test(effectiveIndex)) {
		++m_pawnsCount;
		m_usedPawn.set(effectiveIndex);

		return std::ref(m_pawns[effectiveIndex].InitOrigin(direction));
	}

	return {};
}