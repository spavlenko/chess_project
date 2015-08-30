#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "BoardController.h"
#include "TransitionHistory.h"

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Figure::Side activeSide READ activeSide NOTIFY activeSideChanged)

public:
    explicit GameController(QObject *parent = 0);

    Q_INVOKABLE BoardController* boardController();

    Q_INVOKABLE void save() const;
    Q_INVOKABLE void load();

    Q_INVOKABLE bool prevTransition();
    Q_INVOKABLE bool nextTransition();

    Q_INVOKABLE Figure::Side activeSide() const;

signals:
    void nextAvailable(bool available);
    void prevAvailable(bool available);
    void activeSideChanged(Figure::Side new_active_side);

private:
    void _connectSignals();
    void _notifyTransitionsAvaliability();
    void _resetActiveSide();
    void _swapActiveSide();


private:
    BoardController m_board_controller;
    TransitionHistory m_transition_history;

    Figure::Side m_active_side;

};

#endif // GAMECONTROLLER_H
