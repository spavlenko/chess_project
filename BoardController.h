#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

/*
 * Constorls interaction with Board
 *
*/

#include "Figure.h"
#include "LogicController.h"
#include "Transition.h"

#include <QObject>
#include <QQmlListProperty>


class BoardController : public QObject
{

    Q_PROPERTY(QQmlListProperty<Figure>  board READ board NOTIFY boardChanged )

    Q_OBJECT
public:
    explicit BoardController(QObject *parent = 0);

    Q_INVOKABLE bool moveFigure(int from,  int to);
    Q_INVOKABLE Figure* figureAt(int index);
    Q_INVOKABLE QList<int> availableMoves(int from) const; //????????????????
    Q_INVOKABLE bool isMoveAllowed(int from,  int to);
    Q_INVOKABLE QQmlListProperty<Figure> board();

    Q_INVOKABLE void resetBoard();

    void performTransition(const Transition& transition);
    void rollbackTransition(const Transition& transition);

signals:
    void figureMoved(const Transition& transition);
    void boardChanged (QQmlListProperty<Figure> content);

private:
    void _initBoard();
    void _moveFigure(int from, int to,
                     Figure::Type displacer_type = Figure::NONE,
                     Figure::Side displacer_side = Figure::UNDEF);
    
private:
    QList<Figure*> m_figures;
    LogicController m_logic_controller;

};

#endif // BOARDCONTROLLER_H
