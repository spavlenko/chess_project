#include "GameController.h"

GameController::GameController(QObject *parent) :
    QObject(parent),
    m_board_controller(this)
{
}

BoardController* GameController::boardController()
{
    return &m_board_controller;
}

