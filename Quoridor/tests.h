#pragma once

#include "Board.h"
#include "util_decls.h"
#include "PiecesHandle.h"
#include "req.hh"
#include "GameState.h"
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


Direction charToDirection(char ch);


void test_board();
void test_pieces_handle();
void player_game_loop(Player&, Board&, PiecesHandle& ph);
variant<Position, Err> input_to_position();
variant<Direction, Place, Err> read_input(GameState = GameState::Moving);

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

	// print empty board
	cout << b;

	// place North player and move South
	if (auto playerOpt = Player::MakePlayer(Direction::North, ph)) {
		Player& player = playerOpt.value();
		b.SetupPlayer(player, 0);
		b.MovePawn(player, Direction::South, onFail);
	}

	if (auto playerOpt = Player::MakePlayer(Direction::North, ph)) {
		req(0, "North again?");
	}
	
	// place South Player and start game loop
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
			cout << err.view() << endl;

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

			// idea: when direction for wall is choosen repaint the screen
			// with E4, E1 etc.;

			if (auto placeableWallOpt = player.PickWall(position, direction, ph)) {

				player.PlaceWall(b, placeableWallOpt.value(),
					[&b](bool fited) {
					if (fited) {
						cout << "\nPlacing wall..." << endl;
						system(SYS_CLEAR);
						cout << b << endl;
					}
					else {
						system(SYS_CLEAR);
						cout << b << endl;
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

variant<Direction, Err> parseDirection(const string_view& line)
{
	auto parseValueToDirection = [](ParsedValue<GameState::Moving>& parsedValue, auto) {
		return charToDirection(parsedValue);
	};

	auto parseResult = applyParser<Direction>(line, Parse::Moving, parseValueToDirection);
	if (std::holds_alternative<Direction>(parseResult))
		return std::get<Direction>(parseResult);
	return Err("Invalid direction");
}

variant<Place, Err> parsePlace()
{
	string line;
	cout << "\nPlacing wall ...\nDirection: ";
	std::getline(cin, line);

	auto cancelCheck = applyParser(line, Parse::Quiting);
	if (std::holds_alternative<Success>(cancelCheck))
		return Err("Backing up.");

	auto directionResult = parseDirection(line);
	if (std::holds_alternative<Direction>(directionResult)) {
		auto direction = std::get<Direction>(directionResult);

		return Place{ std::get<Position>(input_to_position()),  direction };
	}
	return Err("Invalid direction");
}

// last
variant<Direction, Place, Err> read_input(GameState gameState)
{
	string line;
	cout << "\nAction: ";
	std::getline(cin, line);

	{
		auto parseResult = applyParser(line, Parse::Quiting);
		if (std::holds_alternative<Success>(parseResult))
			return Exit("Goodbye!");
	}

	{
		auto parseResult = applyParser(line, Parse::Placing);
		if (std::holds_alternative<Success>(parseResult))
			gameState = GameState::Placing;
	}

	switch (gameState)
	{
	case GameState::Moving:
	{
		auto parseResult = parseDirection(line);
		if (std::holds_alternative<Direction>(parseResult))
			return std::get<Direction>(parseResult);
		return Err("Invalid direction");
	}
	case GameState::Placing:
	{
		auto parseResult = parsePlace();
		if (std::holds_alternative<Place>(parseResult))
			return std::get<Place>(parseResult);
		return std::get<Err>(parseResult);
	}
	default:
		return Err("Invalid option.");
	}
}

// todo
variant<Position, Err> input_to_position()
{
	string line;
	Position position;
	auto&[row, col] = position;

	cout << "\nPosition: ";

	try {
		cout << "\nrow: "; cin >> row;

		if (cin.fail())
			throw "Fail";

		cout << "\ncol: "; cin >> col;

		if (cin.fail())
			throw "Fail";

		std::getline(cin, line);
		return position;
	}
	catch (...) {
		cin.clear();
		std::getline(cin, line);
		return Err("Invalid number inserted.");
	}
	cin.clear();
	std::getline(cin, line);
	return Err("Invalid number inserted.");
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


Direction charToDirection(char ch)
{
	switch (ch) {
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
		req(0, "Should've not reached here.");
		return Direction::None; // silence warning
	}
}


//void cinClear()
//{
//	cin.clear();
//	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//}