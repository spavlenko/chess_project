#include "Transition.h"

Transition::Transition(TIndex from, TIndex to, Figure::Side actor, Figure::Type victim)
    : m_from(from)
    , m_to(to)
    , m_actor(actor)
    , m_victim(victim)
{
}
