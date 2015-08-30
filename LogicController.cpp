#include "LogicController.h"
#include "BoardController.h"
#include "Transition.h"


LogicController::LogicController(const BoardController &board, QObject *parent)
    : QObject(parent)
    , m_game_board(board)
{
}

QList<int> LogicController::availableMoves(int from) const
{
    QList<int> res;
    res << from;
    res << 0 << 1 << 8 << 9;

    return res;
}

bool LogicController::isMoveAllowed(int from, int to) const
{
    return from != to;
}

bool LogicController::isTransitionAllowed(const Transition &transition) const
{
    return true;
}


