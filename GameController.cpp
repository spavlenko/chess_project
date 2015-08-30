#include "GameController.h"

#include <QStandardPaths>
#include <QFile>

#include <QDebug>
namespace
{
    const QString save_path =
            QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/chess.save";
}


GameController::GameController(QObject *parent) :
    QObject(parent),
    m_board_controller(this)
{
}

BoardController* GameController::boardController()
{
    return &m_board_controller;
}

void GameController::save() const
{
    QFile file(save_path);

    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Something wrong. Can't open file.";
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
        qDebug() << "Something wrong. Can't open file.";
        return;
    }

    QDataStream stream(&file);
    stream >> m_transition_history;
    file.close();
    boardController()->resetBoard();
    qDebug() << "Game sucessfully laded";
}

void GameController::_connectSignals()
{
    QObject::connect(&m_board_controller, &BoardController::figureMoved,
                     &m_transition_history, &TransitionHistory::add);
}

