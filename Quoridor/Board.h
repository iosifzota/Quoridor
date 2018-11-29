#pragma once

#include "using_matrix.h"
#include "Pawn.h"
#include "Trench.h"
#include "PiecesHandle.h"
#include "util_decls.h"
#include <ostream>
using std::ostream;

/* IDEA: implement option<T> : enum { Some<T>, Err } <=> (somewhat) variant<T, Err> */

using Direction = Piece::Direction;

class Board
{
public:
	enum class MoveResult : char {
		InvalidDirection,
		BlockedDirection,
		Success
	};
	// Ideea: make_position<1>(x, y) that return the same instance (no?)
	void MovePawn(Pawn& candidate, Piece::Direction, function<void(MoveResult, Pawn&, Direction)>);
	Pawn& UpdateStateUponPassingTrench(Pawn&, Direction);

	friend ostream& operator << (ostream&, const Board&);

	// working on here (last time i changed tiles from optional -> OptRef)
	Board(GameType);


public:
	/* Learned (https://en.cppreference.com/w/cpp/language/definition):
	   static const __id__; // declared but not defined
	   inline static const __id__; // defined
	   static const __id__ = __value__; // defined (implicitly inlined)
	   -----
	   https://stackoverflow.com/questions/29397864/why-does-constexpr-static-member-of-type-class-require-a-definition
	   -----
	   If a refereance to any of these atributes is taken, they are odr-used
	   therefore the definition must be included in the compile unit,
	   and it must be defined only once in the whole program.
	   If this header is include in two cpp files that are linked
	   together and both take a reference to WIDTH/HEIGHT, there will be
	   two definitions of the atributes and linking will fail(undefined reference ...) [TO CHECK].
	 */
private: // WARNING: private -> public?
	static const size_t WIDTH = 9;
	static const size_t HEIGHT = 9;

private:
	matrix<OptRef<Pawn>, WIDTH> tiles;
	Trench<WIDTH - 1, HEIGHT> trenchNorthSouth;
	Trench<WIDTH, HEIGHT - 1> trenchEastWest;

	PiecesHandle m_pieces;
};
