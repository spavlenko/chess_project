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

    Q_INVOKABLE void save() const;
    Q_INVOKABLE void load();

    Q_INVOKABLE bool prevTransition();
    Q_INVOKABLE bool nextTransition();


private:
    void _connectSignals();

private:
    BoardController m_board_controller;
    TransitionHistory m_transition_history;

};

#endif // GAMECONTROLLER_H
