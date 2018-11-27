#pragma once

#include "using_matrix.h"
#include "Pawn.h"
#include "Trench.h"
#include <ostream>
#include <optional>
#include <functional>
#include <variant>
using std::optional;
using std::function;
using std::ostream;

using std::variant;
/* TODO: implement option<T> : enum { Some<T>, Err } <=> (somewhat) variant<T, Err> */

using Direction = Piece::Direction;

class Board
{
public:
	enum class MoveResult : char {
		AbsentCandidate,
		InvalidDirection,
		BlockedDirection,
		Success
	};
	// Ideea: make_position<1>(x, y) that return the same instance (no?)
	void MovePawn(Pawn& candidate, Piece::Direction, function<void(MoveResult, Pawn&, Direction)>);
	Pawn& UpdateStateUponPassingTrench(Pawn&, Direction);

	friend ostream& operator << (ostream&, const Board&);

	// working on
	Board();


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
private: // TODO: private -> public?
	static const size_t WIDTH = 9;
	static const size_t HEIGHT = 9;

private:
	// TODO: optional -> reference_wrapper
	matrix<optional<Pawn>, WIDTH> tiles;
	Trench<WIDTH - 1, HEIGHT> trenchNorthSouth;
	Trench<WIDTH, HEIGHT - 1> trenchEastWest;
};
