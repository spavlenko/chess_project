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

    bool isMoveAllowed(int from, int to) const;

    bool isTransitionAllowed(const Transition&  transition) const;

private:
    const BoardController& m_game_board;

};

#endif // LOGICCONTROLLER_H
