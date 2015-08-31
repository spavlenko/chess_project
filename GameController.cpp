#include "GameController.h"

#include <QStandardPaths>
#include <QFile>
#include <QDir>

#include <QDebug>


GameController::GameController(QObject *parent) :
    QObject(parent),
    m_board_controller(this),
    m_mode(INIT)

{
    _connectSignals();
}

BoardController* GameController::boardController()
{
    return &m_board_controller;
}

void GameController::start()
{
    m_transition_history.clear();
    m_board_controller.resetBoard();
    _setMode(GAME);
    _resetActiveSide();
}

void GameController::stop()
{
    m_board_controller.clearBoard();
    m_transition_history.clear();
    _setMode(INIT);
}

void GameController::save(QUrl path) const
{
    QFile file(path.toLocalFile());

    if(!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "Something is wrong. Can't open file.";
        return;
    }
    file.resize(0);

    QDataStream stream(&file);

    stream << m_transition_history;

    file.flush();
    file.close();
    qDebug() << "Game sucessfully saved";
}

void GameController::load(QUrl path)
{
    QFile file(path.toLocalFile());

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Something is wrong. Can't open file.";
        return;
    }

    QDataStream stream(&file);
    stream >> m_transition_history;
    file.close();
    boardController()->resetBoard();
    _notifyTransitionsAvaliability();
    _resetActiveSide();
    _setMode(PLAYBACK);
    qDebug() << "Game sucessfully laded";
}

bool GameController::prevTransition()
{
    if(!m_transition_history.isPrevAvailable())
        return false;

    auto& transition = *(m_transition_history.prev());
    boardController()->rollbackTransition(transition);

    _swapActiveSide();
    _notifyTransitionsAvaliability();
    return true;
}

bool GameController::nextTransition()
{
    if(!m_transition_history.isNextAvailable())
        return false;

    auto& transition = *(m_transition_history.next());
    boardController()->performTransition(transition);

    _swapActiveSide();
    _notifyTransitionsAvaliability();
    return true;
}

Figure::Side GameController::activeSide() const
{
    return m_active_side;
}

GameController::Mode GameController::mode() const
{
    return m_mode;
}

void GameController::_connectSignals()
{
    QObject::connect(&m_board_controller, &BoardController::figureMoved,
                     &m_transition_history, &TransitionHistory::add);

    QObject::connect(&m_board_controller, &BoardController::figureMoved,
                     [this](){_swapActiveSide();});

    QObject::connect(&m_transition_history, &TransitionHistory::historyChanged,
                     [this](){_notifyTransitionsAvaliability();});

}

void GameController::_notifyTransitionsAvaliability()
{
    emit nextAvailable(m_transition_history.isNextAvailable());
    emit prevAvailable(m_transition_history.isPrevAvailable());
}

void GameController::_resetActiveSide()
{
    m_active_side = Figure::WHITE;

    emit activeSideChanged(m_active_side);
}

void GameController::_swapActiveSide()
{
    m_active_side = m_active_side == Figure::WHITE ? Figure::BLACK : Figure::WHITE;

    emit activeSideChanged(m_active_side);
}

void GameController::_setMode(GameController::Mode m)
{
    m_mode = m;
    modeChanged(m_mode);
}

