#include "Board.h"
#include "req.hh"
#include <iostream>

Pawn& Board::UpdateStateUponPassingTrench(Pawn& passing, Direction direction)
{
	req(Piece::validDirection(direction));
	auto[x_old, y_old] = passing.AccessPosition(); // save current position
	req(tiles[x_old][y_old].has_value());

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

void Board::MovePawn(Pawn& candidate, Direction direction, function<void(MoveResult, Pawn&, Direction)> postMoveAction)
{
	// DONE try and see what candidate state is after UpdateState
	auto result = MoveResult::BlockedDirection;
	auto&[x, y] = candidate.AccessPosition();

	switch (direction) {
	case Direction::North: case Direction::East:
		if (!trenchNorthSouth.AtBackward(x, y)) {
			UpdateStateUponPassingTrench(candidate, direction);
			result = MoveResult::Success;
		}
		break;
	case Direction::South: case Direction::West:
		if (!trenchNorthSouth.AtForward(x, y)) {
			UpdateStateUponPassingTrench(candidate, direction);
			result = MoveResult::Success;
		}
		break;
	default:
		result = MoveResult::InvalidDirection;
	}

	postMoveAction(result, candidate, direction);
}


Board::Board(GameType gameType) :
	m_pieces{gameType}
{
	Position pos{ 0, 0 };
	auto&[x, y] = pos;

	Pawn& pawn = m_pieces.GetPawn(Direction::North, pos).value();
	pawn.AccessPosition() = pos;

	tiles[y][x].emplace(pawn);

	std::cout << *this << "\n------------------------------------\n";

	MovePawn(tiles[y][x].value(), Direction::South,
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