#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "Types.h"

#include <QObject>
#include <QList>

class BoardController;
class Transition;

class LogicController : public QObject
{
    Q_OBJECT
public:
    explicit LogicController(const BoardController& board, QObject *parent = 0);

    QList<TIndex> availableMoves(TIndex from) const;
    bool isMoveAllowed(TIndex from, TIndex to) const;
    bool isTransitionAllowed(const Transition&  transition) const;

private:
    const BoardController& m_game_board;

};

#endif // LOGICCONTROLLER_H
