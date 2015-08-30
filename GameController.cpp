#include "GameController.h"

#include <QStandardPaths>
#include <QFile>
#include <QDir>


#include <QDebug>
namespace
{
    const QString save_path =
            QStandardPaths::writableLocation(QStandardPaths::TempLocation)
            +  QDir::separator() + "chess.save";
}

GameController::GameController(QObject *parent) :
    QObject(parent),
    m_board_controller(this)
{
    _connectSignals();
}

BoardController* GameController::boardController()
{
    return &m_board_controller;
}

void GameController::save() const
{
    QFile file(save_path);

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

void GameController::load()
{
    QFile file(save_path);

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Something is wrong. Can't open file.";
        return;
    }

    QDataStream stream(&file);
    stream >> m_transition_history;
    file.close();
    boardController()->resetBoard();
    _notifyTransitionsAvaliability();
    qDebug() << "Game sucessfully laded";
}

bool GameController::prevTransition()
{
    if(!m_transition_history.isPrevAvailable())
        return false;

    auto& transition = *(m_transition_history.prev());
    boardController()->rollbackTransition(transition);

    _notifyTransitionsAvaliability();
    return true;
}

bool GameController::nextTransition()
{
    if(!m_transition_history.isNextAvailable())
        return false;

    auto& transition = *(m_transition_history.next());
    boardController()->performTransition(transition);

    _notifyTransitionsAvaliability();
    return true;
}

void GameController::_connectSignals()
{
    QObject::connect(&m_board_controller, &BoardController::figureMoved,
                     &m_transition_history, &TransitionHistory::add);

    QObject::connect(&m_transition_history, &TransitionHistory::historyChanged,
                     [this](){_notifyTransitionsAvaliability();});
}

void GameController::_notifyTransitionsAvaliability()
{
    emit nextAvailable(m_transition_history.isNextAvailable());
    emit prevAvailable(m_transition_history.isPrevAvailable());
}

