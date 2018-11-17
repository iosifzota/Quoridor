#pragma once

#include "matrix.h"
#include "Pawn.h"
#include <optional>
#include <functional>
#include <variant>
using std::optional;
using std::function;
using std::variant;

using PawnOpt = optional<Pawn>;

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
        void MovePawn(PawnOpt& candidate, Piece::Direction, function<void(MoveResult)>); // HERE

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
           So if this header is include in two cpp files that are linked
           together and both take a reference to WIDTH/HEIGHT there will be
           two definitions of the atributes and the linking will fail(undefined reference ...) [TO CHECK] .
         */
private: // TODO: private -> public?
        static const size_t WIDTH = 9;
        static const size_t HEIGHT = 9;

private:

        matrix<optional<Pawn>, WIDTH> tiles;
        Trench<WIDTH, HEIGHT-1> trenchNorthSouth;
        Trench<WIDTH-1, HEIGHT> trenchEastWest;
};
