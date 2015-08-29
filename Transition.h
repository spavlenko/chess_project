#ifndef TRANSITION_H
#define TRANSITION_H

#include "Figure.h"
#include "Types.h"

class Transition
{
public:
    Transition(TIndex from, TIndex to, Figure::Side actor, Figure::Type victim);

public:
    TIndex m_from;
    TIndex m_to;
    Figure::Side m_actor;
    Figure::Type m_victim;


};

#endif // TRANSITION_H
