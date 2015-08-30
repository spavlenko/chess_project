#include "BoardController.h"
#include <QDebug>

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
    auto victim  =  figureAt(to);
    auto victim_type  = victim->type();
    auto victim_color = victim->side();

    Transition t(from, to, victim_color, victim_type);
    _moveFigure(from, to);
    emit figureMoved(t);
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

void BoardController::performTransition(const Transition &transition)
{
    _moveFigure(transition.m_from, transition.m_to);
}

void BoardController::rollbackTransition(const Transition &transition)
{
    _moveFigure(transition.m_to, transition.m_from, transition.m_victim_type, transition.m_victim_side);
}

void BoardController::_initBoard()
{
    m_figures.clear();

    for(int i = 0; i < 64; ++i)
        m_figures.append(new Figure(this, _ChooseFigure(i), _ChooseSide(i)));
}

void BoardController::_moveFigure(int from, int to, Figure::Type displacer_type, Figure::Side displacer_side)
{
    std::swap(m_figures[from], m_figures[to]);
    auto displacer = m_figures[from];
    displacer->setType(displacer_type);
    displacer->setSide(displacer_side);

    qDebug() << "Move from " << from  << " to " << to;

    emit boardChanged(board());
}




