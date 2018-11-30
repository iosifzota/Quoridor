#pragma once

#include "Board.h"
#include "util_decls.h"
#include "PiecesHandle.h"
#include "req.hh"
#include <iostream>
#include <string>
#include <string_view>
using std::string;
using std::string_view;
using std::cout;
using std::endl;
using std::cin;

void test_board();
void test_pieces_handle();
void player_game_loop(Player&, Board&);
variant<Direction, string_view> input_to_direction();

void tests()
{
	test_board();
	test_pieces_handle();
}

void test_board()
{
	cout << __FUNCTION__ << ":\n";

	function<void(Board::MoveResult, Pawn&, Direction)> onFail =
		[](auto mr, auto, auto) {
		if (Board::MoveResult::Success != mr)
			cout << "Failed to move\n";
	};

	Board b;
	PiecesHandle ph(GameType::TwoPlayers);

	cout << b;

	if (auto playerOpt = Player::MakePlayer(Direction::North, ph)) {
		Player& player = playerOpt.value();
		b.SetupPlayer(player, 0);

		cout << b;
		b.MovePawn(player, Direction::South, onFail);
		cout << "\n----------------------------------\n";
		cout << b;
	}

	if (auto playerOpt = Player::MakePlayer(Direction::North, ph)) {
		req(0, "North again?");
	}

	if (auto playerOpt = Player::MakePlayer(Direction::South, ph)) {
		Player& player = playerOpt.value();

		// here last time
		cout << "\n---------SOUTH------------\n";
		b.SetupPlayer(player, 5);
		cout << b << endl;
		player_game_loop(player, b);
	}
}

void player_game_loop(Player& player, Board& b)
{
	cout << __FUNCTION__ << " coming up.\n";
	system(SYS_PAUSE); system(SYS_CLEAR);
	cout << b << endl;

	while (true) {
		auto ioResult = input_to_direction();

		if (std::holds_alternative<string_view>(ioResult)) {
			system(SYS_CLEAR);
			cout << b << endl;
			cout << std::get<string_view>(ioResult);
			continue;
		}

		auto direction = std::get<Direction>(ioResult);

		if (Direction::None == direction) {
			cout << "Finish" << endl;
			break;
		}

		b.MovePawn(player, direction,
			[&b](Board::MoveResult mr, Pawn&, Direction) {
			system(SYS_CLEAR);
			cout << b << endl;
			if (Board::MoveResult::Success != mr)
				cout << "Failed to move\n";
		});
	}
}

void test_pieces_handle()
{
	cout << __FUNCTION__ << ":\n";
	PiecesHandle ph(GameType::TwoPlayers);

	if (auto pawnOpt = ph.GetPawn(Direction::North)) {
		Pawn& pawn = pawnOpt.value().get();
		cout << "Pawn: " << (int)pawn.GetOrigin() << endl;
	}

	if (auto pawnOpt = ph.GetPawn(Direction::North)) {
		Pawn& pawn = pawnOpt.value().get();
		cout << "Pawn: " << (int)pawn.GetOrigin() << endl;
	}

	if (auto pawnOpt = ph.GetPawn(Direction::South)) {
		Pawn& pawn = pawnOpt.value().get();
		cout << "Pawn: " << (int)pawn.GetOrigin() << endl;
	}
}


variant<Direction, string_view> input_to_direction()
{
	string line;
	std::getline(cin, line);

	if (line.empty())
		return input_to_direction();

	string_view sv(line.c_str());
	size_t optionIndex = sv.find_first_of("wasdWASDqQ");

	static const string_view invalidMsg("Invalid option. Usage: wasd\n");
	if (string::npos == optionIndex) {
		return invalidMsg;
	}

	switch (sv[optionIndex]) {
	case 'w': case 'W':
		return Direction::North;
	case 'a': case 'A':
		return Direction::West;
	case 's': case 'S':
		return Direction::South;
	case 'd': case 'D':
		return Direction::East;
	case 'q': case 'Q':
		return Direction::None;
	default:
		return invalidMsg;
	}
}