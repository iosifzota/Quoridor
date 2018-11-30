#include "Board.h"
#include "req.hh"
#include <iostream>

Pawn& Board::UpdateStateUponPassingTrench(Pawn& passing, Direction direction)
{
	auto[x_old, y_old] = passing.AccessPosition(); // save current position

	// update to next position
	Piece::ApplyDirectionMask(passing.AccessPosition(), direction);

	// effectively move the pawn
	auto&[x, y] = passing.AccessPosition();
	req(!tiles[x][y].has_value(), "Update only after check.");

	tiles[x][y].swap(tiles[x_old][y_old]);
	req(tiles[x][y].has_value(), "[Debug]");
	req(!tiles[x_old][y_old].has_value(), "[Debug]");
	req(&tiles[x][y].value().get() == &passing, "[Debug]");

	return passing;
}

void Board::MovePawn(Player& player, Direction direction, function<void(MoveResult, Pawn&, Direction)> postMoveAction)
{
	auto& pawn = player.AccessPawn();
	req(IsPawnSynced(pawn));
	req(Piece::validDirection(direction));
	// DONE try and see what candidate state is after UpdateState
	auto result = MoveResult::BlockedDirection;
	auto&[x, y] = pawn.AccessPosition();

	switch (direction) {
	case Direction::North:
		if (!trenchNorthSouth.AtBackward(x, y)) {
			UpdateStateUponPassingTrench(pawn, direction);
			result = MoveResult::Success;
		}
		break;
	case Direction::West:
		if (!trenchWestEast.AtBackward(x, y)) {
			UpdateStateUponPassingTrench(pawn, direction);
			result = MoveResult::Success;
		}
		break;
	case Direction::South:
		if (!trenchNorthSouth.AtForward(x, y)) {
			UpdateStateUponPassingTrench(pawn, direction);
			result = MoveResult::Success;
		}
		break;
	case Direction::East:
		if (!trenchWestEast.AtForward(x, y)) {
			UpdateStateUponPassingTrench(pawn, direction);
			result = MoveResult::Success;
		}
		break;
		break;
	default:
		result = MoveResult::InvalidDirection;
	}

	postMoveAction(result, pawn, direction);
}

// last in this file
void Board::SetupPlayer(Player& player, int lineIndex)
{
	auto& pawn = player.AccessPawn();
	req(!Piece::validPosition(pawn.GetPosition()), "Unplaced pawn should have invalid position.");
	req(Piece::validDirection(pawn.GetOrigin()), "[Debug]");

	req(lineIndex < tiles.size());

	int effectiveIndex = static_cast<int>(pawn.GetOrigin());
	// TODO take ph& as arg, and use m_usedPawn from there also?.
	req(!m_usedPawns.test(effectiveIndex), "One player per pawn type");
	m_usedPawns.set(effectiveIndex);

	auto&[row, col] = pawn.AccessPosition();

	switch (pawn.GetOrigin())
	{
	case Direction::North:
		row = 0;
		col = lineIndex;
		break;
	case Direction::South:
		row = static_cast<int>(tiles.size()) - 1;
		col = lineIndex;
		break;
	case Direction::East:
		row = lineIndex;
		col = static_cast<int>(tiles.size()) - 1;
		break;
	case Direction::West:
		row = lineIndex;
		col = 0;
		break;
	}

	tiles[row][col].emplace(pawn);
}


void Board::PlaceWall(Player& player, PlaceableWall& placeableWall, function<void(bool)> proc)
{
	auto& pawn = player.AccessPawn();

	if (!IsPawnSynced(player.AccessPawn()) ||
		!m_usedPawns.test(static_cast<int>(pawn.GetOrigin())) ||
		!player.WallCount()) {

		proc(false);
		return;
	}

	bool fits = WAllFitsDo(placeableWall,
		[&](auto oneHalf, auto otherHalf) {
		auto&[row, col] = oneHalf;
		auto&[other_row, other_col] = otherHalf;

		switch (placeableWall.GetDirection())
		{
		case Direction::North: case Direction::South:
			trenchWestEast.OccupyTrench(row, col);
			trenchWestEast.OccupyTrench(other_row, other_col);
			break;

		case Direction::West: case Direction::East:
			trenchNorthSouth.OccupyTrench(row, col);
			trenchNorthSouth.OccupyTrench(other_row, other_col);
			break;
		default:
			break;
		}
	});

	proc(fits);
}

bool Board::WAllFitsDo(const PlaceableWall& placeableWall, function<void(const Position&, const Position&)> onFit)
{
	auto&[row, col] = placeableWall.GetPosition();
	auto direction = placeableWall.GetDirection();

	Position otherHalf(placeableWall.GetPosition());
	auto&[other_row, other_col] = otherHalf;

	Piece::ApplyDirectionMask(otherHalf, direction);

	switch (direction)
	{
	case Direction::North: case Direction::South:
		if (!trenchWestEast.AtForward(row, col) &&
			!trenchWestEast.AtForward(other_row, other_col))
		{
			onFit(placeableWall.GetPosition(), otherHalf);
			return true;
		}
		break;

	case Direction::West: case Direction::East:
		if (!trenchNorthSouth.AtForward(row, col) &&
			!trenchNorthSouth.AtForward(other_row, other_col))
		{
			onFit(placeableWall.GetPosition(), otherHalf);
			return true;
		}
		break;
	}
	return false;
}

bool Board::IsPawnSynced(const Pawn& pawn) const
{
	if (!Piece::validDirection(pawn.GetOrigin()) ||
		!Piece::validPosition(pawn.GetPosition()))
		return false;

	auto&[row, col] = pawn.GetPosition();

	if (!tiles[row][col].has_value())
		return false;

	return &tiles[row][col].value().get() == &pawn;
}

ostream& operator<<(ostream& out, const Board& board)
{
	auto& tiles = board.tiles;
	auto& trenchWestEast = board.trenchWestEast;
	auto& trenchNorthSouth = board.trenchNorthSouth;
	const char* temp = nullptr;
	// IDEA: implement range
	for (size_t row = 0; row < tiles.size(); ++row) {
		for (size_t col = 0; col < tiles.size(); ++col) {
			temp = tiles[row][col].has_value() ? " x " : "   ";
			out << temp;

			if (col + 1 < tiles.size()) {
				temp = trenchWestEast.AtForward(row, col) ? "|" : ":";
				out << temp;
			}
		}
		out << '\n';
		if (row + 1 < tiles.size()) {
			for (size_t col = 0; col < trenchNorthSouth.Width(); ++col) {
				temp = trenchNorthSouth.AtForward(row, col) ? "--- " : "... ";
				out << temp;
			}
			out << '\n';
		}
	}
	return out;
}


Board::Board() :
	m_usedPawns{}
{
}