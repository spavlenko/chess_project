#include "LogicController.h"
#include "BoardController.h"
#include "Transition.h"


LogicController::LogicController(const BoardController &board, QObject *parent)
    : QObject(parent)
    , m_game_board(board)
{
}

QList<TIndex> LogicController::availableMoves(TIndex from) const
{
    QList<TIndex> res;
    res << from;
    res << 0 << 1 << 8 << 9;

    return res;
}

bool LogicController::isMoveAllowed(TIndex from, TIndex to) const
{
    return from != to;
}

bool LogicController::isTransitionAllowed(const Transition &transition) const
{
    return true;
}


