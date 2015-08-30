#include "LogicController.h"
#include "BoardController.h"
#include "FiguresMoveRules.h"

#include "Transition.h"


LogicController::LogicController(const BoardController &board, QObject *parent)
    : QObject(parent)
    , m_game_board(board)
{
}


bool LogicController::isMoveAllowed(int from, int to) const
{
    auto figure = m_game_board.figureAt(from);
    auto target = m_game_board.figureAt(to);

    if(figure->side() == target->side())
        return false;

    if(!isMoveValid(figure->type(), figure->side(), from, to, target->side() != Figure::UNDEF))
        return false;

    if(!isPositionAccessible(figure->type(), from, to, m_game_board))
        return false;

    return true;
}



