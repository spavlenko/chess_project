#include "BoardController.h"

namespace {
  Figure::Side _ChooseSide(int index)
  {
      auto row = index / board_size;

      if(row < 2)
        return Figure::Side::BLACK;

      if (row > 5)
        return Figure::Side::WHITE;

      return Figure::Side::UNDEF;
  }

  Figure::Type _ChooseFigure(int index)
  {
      auto row = index / board_size;

      if(row == 1 || row == 6)
        return Figure::Type::PAWN;
      else if(row != 0 && row != 7)
        return Figure::Type::NONE;

      auto column = index % board_size;
      switch(column)
      {
      case 0: case 7:
        return Figure::Type::ROOK;
      case 1: case 6:
        return Figure::Type::KNIGHT;
      case 2: case 5:
        return Figure::Type::BISHOP;
      case 3:
        return Figure::Type::QUEEN;
      case 4:
        return Figure::Type::KING;
      }

      return Figure::Type::NONE;
  }

}

BoardController::BoardController(QObject *parent) :
    QObject(parent) ,
    m_logic_controller(*this)
{
    _initBoard();
}

const LogicController &BoardController::getLogicController() const
{
    return m_logic_controller;
}

bool BoardController::moveFigure(int from, int to)
{
    if(!m_logic_controller.isMoveAllowed(from, to))
        return false;

    auto victim = figureAt(to)->type();
    auto actor = figureAt(from)->side();

    std::swap(m_figures[from], m_figures[to]);

    Transition t(from, to, actor, victim);
    emit figureMoved(t);
    emit boardChanged(board());
    return true;
}

Figure *BoardController::figureAt(int index)
{
    return m_figures.at(index);
}

QQmlListProperty<Figure> BoardController::board()
{
    return QQmlListProperty<Figure> (this, m_figures);
}

void BoardController::resetBoard()
{
    _initBoard();
    emit boardChanged(board());
}

void BoardController::_initBoard()
{
    m_figures.clear();

    for(int i = 0; i < 64; ++i)
        m_figures.append(new Figure(this, _ChooseFigure(i), _ChooseSide(i)));
}




