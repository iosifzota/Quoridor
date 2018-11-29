#pragma once

#include "Pawn.h"
#include <array>
#include <optional>
#include <functional>
using std::array;
using std::size_t;
using std::optional;
using Direction = Piece::Direction;

template <typename T>
using ref_wrapper = std::reference_wrapper<T>;

class PiecesHandle
{
public:
	PiecesHandle(size_t);

	optional<ref_wrapper<Pawn>> GetPawn(Direction direction);
	const size_t m_wallsPerPlayer;

private:
	const size_t m_playerCount;
	static const size_t TOTAL_WALLS = 16;
	static const size_t MAX_PLAYERS = 4;
	array<Pawn, MAX_PLAYERS> m_pawns;

	// helpers
	size_t m_pawnsCount;
	Piece::ValidDirectionChecklist m_usedPawn;
};
