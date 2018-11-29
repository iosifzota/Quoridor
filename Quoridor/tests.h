#pragma once

#include "Board.h"
#include "util_decls.h"
#include "PiecesHandle.h"
#include <iostream>
using std::cout;
using std::endl;

void test_board();
void test_pieces_handle();

void tests()
{
	test_board();
	test_pieces_handle();
}

void test_board()
{
	cout << __FUNCTION__ << ":\n";
	Board b(GameType::TwoPlayers);
	cout << b;
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