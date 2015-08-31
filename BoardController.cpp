#include "BoardController.h"
#include "Constants.h"
#include <QDebug>

namespace {
  Figure::Side _ChooseSide(int index)
  {
      auto row = index / Constants::board_size;

      if(row <= Constants::black_second_row )
        return Figure::Side::BLACK;

      if (row >= Constants::white_second_row)
        return Figure::Side::WHITE;

      return Figure::Side::UNDEF;
  }

  Figure::Type _ChooseFigure(int index)
  {
      auto row = index / Constants::board_size;

      if(row == Constants::white_second_row || row == Constants::black_second_row)
        return Figure::Type::PAWN;

      else if(row != Constants::white_first_row && row != Constants::black_first_row)
        return Figure::Type::NONE;

      auto column = index % Constants::board_size;
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

  const int board_items_count = Constants::board_size * Constants::board_size;

}

BoardController::BoardController(QObject *parent) :
    QObject(parent) ,
    m_logic_controller(*this)
{
    clearBoard();
}

bool BoardController::moveFigure(int from, int to)
{
    if(!m_logic_controller.isMoveAllowed(from, to) || from == to)
        return false;
    auto victim  =  figureAt(to);
    auto victim_type  = victim->type();
    auto victim_color = victim->side();

    Transition t(from, to, victim_color, victim_type);
    _moveFigure(from, to);
    emit figureMoved(t);
    return true;
}

const Figure *BoardController::figureAt(int index) const
{
    return m_figures.at(index);
}

bool BoardController::isMoveAllowed(int from, int to)
{
    return m_logic_controller.isMoveAllowed(from, to);
}

QQmlListProperty<Figure> BoardController::board()
{
    return QQmlListProperty<Figure> (this, m_figures);
}

void BoardController::clearBoard()
{
    m_figures.clear();

    for(int i = 0; i < board_items_count; ++i)
        m_figures.append(new Figure(this, Figure::Type::NONE, Figure::Side::UNDEF));

    emit boardChanged(board());
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

    for(int i = 0; i < board_items_count; ++i)
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




