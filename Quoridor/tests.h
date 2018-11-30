#pragma once

#include "Board.h"
#include "util_decls.h"
#include "PiecesHandle.h"
#include "req.hh"
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
using std::pair;
using std::tuple;
using std::string;
using std::string_view;
using std::cout;
using std::endl;
using std::cin;

enum class GameState :char {
	Moving,
	Placing
};

using Place = std::pair<Position, Direction>;

struct Err {
	Err(const char* str, bool exit = false) :
		m_msg{ str },
		m_exit{ exit }
	{}
	string_view view() const {
		return m_msg.c_str();
	}
	bool exit() const {
		return m_exit;
	}

	bool m_exit;
	const string m_msg;
};

struct Exit : Err {
	Exit(const char* str) :
		Err(str, true)
	{}
};

void test_board();
void test_pieces_handle();
void player_game_loop(Player&, Board&, PiecesHandle& ph);
variant<Direction, string_view> input_to_direction();
variant<Position, string_view> input_to_position();
optional<GameState> input_to_state();
variant<Direction, Place, Err> read_input();

variant<Place, Err> input_to_place();

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

		cout << "\n---------Playing------------\n";
		b.SetupPlayer(player, 5);
		cout << b << endl;

		// here last time
		player_game_loop(player, b, ph);
	}
}

void player_game_loop(Player& player, Board& b, PiecesHandle& ph)
{
	cout << __FUNCTION__ << " coming up.\n";
	system(SYS_PAUSE); system(SYS_CLEAR);
	cout << b << endl;

	while (true) {
		variant<Direction, Place, Err> ioResult = read_input();

		if (std::holds_alternative<Err>(ioResult)) {
			const Err& err = std::get<Err>(ioResult);

			system(SYS_CLEAR);
			cout << b << endl;
			cout << err.view();

			if (err.exit()) {
				break;
			}
			continue;
		}
		else if (std::holds_alternative<Direction>(ioResult)) {
			auto direction = std::get<Direction>(ioResult);

			req(Direction::None != direction);

			b.MovePawn(player, direction,
				[&b](Board::MoveResult mr, Pawn&, Direction) {
				system(SYS_CLEAR);
				cout << b << endl;
				if (Board::MoveResult::Success != mr)
					cout << "Failed to move\n";
			});
		}
		else {
			auto&[position, direction] = std::get<Place>(ioResult);

			if (auto placeableWallOpt = player.PickWall(position, direction, ph)) {

				player.PlaceWall(b, placeableWallOpt.value(),
					[&b](bool fited) {
					if (fited) {
						cout << "\nPlacing wall..." << endl;
						system(SYS_CLEAR);
						cout << b << endl;
					}
					else {
						cout << "\nCannot place wall there." << endl;
					}
				});
			}
			else {
				cout << "\nNo more walls available for player." << endl;
			}
		}
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

variant<Direction, Place, Err> read_input()
{
	auto gameState = GameState::Moving;

	if (auto gameStateRead = input_to_state()) {
		if (gameStateRead.value() != gameState)
			gameState = gameStateRead.value();
	}

	switch (gameState)
	{
	case GameState::Moving: {
		auto ioResult = input_to_direction();

		if (std::holds_alternative<string_view>(ioResult))
			return Err(std::get<string_view>(ioResult).data());

		// exit on None direction
		auto direction = std::get<Direction>(ioResult);
		if (Direction::None == direction) {
			return Exit("Goodbye!");
		}

		return std::get<Direction>(ioResult);
	}
	case GameState::Placing: {
		auto ioResult = input_to_place();

		if (std::holds_alternative<Err>(ioResult))
			return std::get<Err>(ioResult);
		return std::get<Place>(ioResult);
	}
	}
	return Exit("[Debug]");
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
	if (string_view::npos == optionIndex) {
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

optional<GameState> input_to_state()
{
	string line;

	cout << "\nAction: ";
	std::getline(cin, line); // big time what?

	if (line.empty())
		return {};

	string_view sv(line.c_str());
	size_t optionIndex = sv.find_first_of("pPmM");

	if (string_view::npos == optionIndex) {
		return {};
	}

	switch (sv[optionIndex]) {
	case 'p': case 'P':
		return GameState::Placing;
	case 'm': case 'M':
		return GameState::Moving;
	}
	return {};
}


variant<Place, Err> input_to_place()
{
	cout << "\nDirection:";
	auto ioResult = input_to_direction();

	if (std::holds_alternative<string_view>(ioResult)) {
		return Err(std::get<string_view>(ioResult).data());
	}

	auto direction = std::get<Direction>(ioResult);

	if (Direction::None == direction) {
		return Exit("Goodbye!");
	}

	return Place{ std::get<Position>(input_to_position()),  direction };
}


variant<Position, string_view> input_to_position()
{
	string line;
	Position position;
	auto&[row, col] = position;

	cout << "\nPosition: ";
	cout << "\nrow: ";
	cin >> row;
	cout << "\ncol: ";
	cin >> col;
	std::getline(cin, line); // eat \n (really strange); see 'big time what?'

	return position;
}