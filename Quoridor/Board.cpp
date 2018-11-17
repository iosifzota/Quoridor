#include "Board.h"

// HERE
void Board::MovePawn(PawnOpt& candidate, Direction direction, function<void(MoveResult)> postMoveAction)
{
        MoveResult result = MoveResult::BlockedDirection;
        if (PawnOpt.has_value()) {
                switch (direction) {
                        auto& [x, y] = candidate.GetPosition();
                case Direction::North:
                        if (trenchNorthSouth.AtBackward(x, y)) {
                                tiles[x][y].emplace(std::move(PawnOpt));
                                result = MoveResult::Success;
                        }
                        break;
                case Direction::South:
                        if (trenchNorthSouth.AtForward(x, y)) {
                                tiles[x][y].emplace(std::move(PawnOpt));
                                result = MoveResult::Success;
                        }
                        break;
                case Direction::East:
                        if (trenchEastWest.AtBackward(x, y)) {
                                tiles[x][y].emplace(std::move(PawnOpt));
                                result = MoveResult::Success;
                        }
                        break;
                case Direction::West:
                        if (trenchEastWest.AtForward(x, y)) {
                                result = tiles[x][y].emplace(std::move(PawnOpt));
                                MoveResult::Success;
                        }
                        break;
                default:
                        result = MoveResult::InvalidDirection;
                }
        }
        postMoveAction(result);
}
