#include "Board.h"
#include "req.hh"
#include <iostream>

Pawn& Board::UpdateStateUponPassingTrench(Pawn& passing, Direction direction)
{
	req(Direction::None != direction);

	auto[x_old, y_old] = passing.AccessPosition(); // save current position
	req(tiles[x_old][y_old].has_value());

	// update to next position
	Piece::ApplyDirectionMask(passing.AccessPosition(), direction);

	// effectively move the pawn
	auto&[x, y] = passing.AccessPosition();
	req(!tiles[x][y].has_value(), "Update only after check.");

	tiles[x][y].swap(tiles[x_old][y_old]);
	req(tiles[x][y].has_value());
	req(!tiles[x_old][y_old].has_value());
	req(&tiles[x][y].value() != &passing, "Testing");

	return tiles[x][y].value();
}



void Board::MovePawn(Pawn& candidate, Direction direction, function<void(MoveResult, Pawn&, Direction)> postMoveAction)
{
	// TODO try and see what candidate has after UpdateState
	auto result = MoveResult::BlockedDirection;
	Pawn *movedPawn = nullptr;
	auto&[x, y] = candidate.AccessPosition();
	switch (direction) {
	case Direction::North: case Direction::East:
		if (!trenchNorthSouth.AtBackward(x, y)) {
			movedPawn = &UpdateStateUponPassingTrench(candidate, direction);
			result = MoveResult::Success;
		}
		break;
	case Direction::South: case Direction::West:
		if (!trenchNorthSouth.AtForward(x, y)) {
			movedPawn = &UpdateStateUponPassingTrench(candidate, direction);
			result = MoveResult::Success;
		}
		break;
	default:
		result = MoveResult::InvalidDirection;
	}

	if (MoveResult::Success == result) {
		req(movedPawn != nullptr);
		postMoveAction(result, *movedPawn, direction);
		return;
	}
	req(movedPawn == nullptr);
	postMoveAction(result, candidate, direction);
}


Board::Board() {
	Position pos{ 0, 0 };
	tiles[0][0].emplace(pos, Direction::North);
	MovePawn(tiles[0][0].value(), Direction::South,
		[](MoveResult res, Pawn& pawn, Direction direction)
	{
	});
}

ostream& operator<<(ostream& out, const Board& board)
{
	auto& tiles = board.tiles;
	auto& trenchEastWest = board.trenchEastWest;
	auto& trenchNorthSouth = board.trenchNorthSouth;
	const char* temp = nullptr;
	// TODO: implement range
	// idea: matrix(char) display
	for (size_t row = 0; row < tiles.size(); ++row) {
		for (size_t col = 0; col < tiles.size(); ++col) {
			temp = tiles[row][col].has_value() ? " x " : "   ";
			out << temp;

			if (col + 1 < tiles.size()) {
				temp = trenchEastWest.AtForward(row, col) ? "|" : ":";
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