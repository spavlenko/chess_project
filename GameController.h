#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "BoardController.h"
#include "TransitionHistory.h"

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT

public:
    enum Mode
    {
        INIT,
        GAME,
        PLAYBACK
    };

    Q_ENUMS(Mode)
    Q_PROPERTY(Mode mode READ mode NOTIFY modeChanged)
    Q_PROPERTY(Figure::Side activeSide READ activeSide NOTIFY activeSideChanged)

public:
    explicit GameController(QObject *parent = 0);

    Q_INVOKABLE BoardController* boardController();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    Q_INVOKABLE void save() const;
    Q_INVOKABLE void load();

    Q_INVOKABLE bool prevTransition();
    Q_INVOKABLE bool nextTransition();

    Q_INVOKABLE Figure::Side activeSide() const;
    Q_INVOKABLE Mode mode() const;

signals:
    void nextAvailable(bool available);
    void prevAvailable(bool available);

    void activeSideChanged(Figure::Side new_active_side);
    void modeChanged(Mode new_mode);

private:
    void _connectSignals();
    void _notifyTransitionsAvaliability();
    void _resetActiveSide();
    void _swapActiveSide();
    void _setMode(Mode m);


private:
    BoardController m_board_controller;
    TransitionHistory m_transition_history;

    Figure::Side m_active_side;
    Mode m_mode;

};

#endif // GAMECONTROLLER_H
