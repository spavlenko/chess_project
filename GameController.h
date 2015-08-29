#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "BoardController.h"
#include "TransitionHistory.h"

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = 0);

    Q_INVOKABLE BoardController* boardController();


private:
    BoardController m_board_controller;
    TransitionHistory m_transition_history;

};

#endif // GAMECONTROLLER_H
