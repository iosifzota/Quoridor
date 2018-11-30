#include "Piece.h"
#include "Trench.h"
#include "tests.h"
#include "PlaceableWall.h"

int main()
{
        Piece p;
        Trench<3,3> t;
		PlaceableWall& wallRef = PlaceableWall::GetInstance({ 1, 1 }, Piece::Direction::North).value();
        tests();
	return 0;
}
