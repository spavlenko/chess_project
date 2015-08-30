#ifndef TRANSITION_H
#define TRANSITION_H

#include "Figure.h"
#include "Types.h"

#include <QDataStream>

class Transition
{
public:
    Transition();
    Transition(int from, int to, Figure::Side victim_side, Figure::Type victim_type);

public:
    qint16 m_from = -1;
    qint16 m_to = -1;
    Figure::Side m_victim_side = Figure::UNDEF;
    Figure::Type m_victim_type = Figure::NONE;
};

 QDataStream &operator<<(QDataStream &data, const Transition &transition);
 QDataStream &operator>>(QDataStream &data, Transition &transition);

#endif // TRANSITION_H
