#ifndef TRANSITION_H
#define TRANSITION_H

#include "Figure.h"
#include "Types.h"

#include <QDataStream>

class Transition
{
public:
    Transition();
    Transition(TIndex from, TIndex to, Figure::Side actor, Figure::Type victim);

public:
    qint16 m_from = -1;
    qint16 m_to = -1;
    Figure::Side m_actor = Figure::UNDEF;
    Figure::Type m_victim = Figure::NONE;
};

 QDataStream &operator<<(QDataStream &data, const Transition &transition);
 QDataStream &operator>>(QDataStream &data, Transition &transition);

#endif // TRANSITION_H
