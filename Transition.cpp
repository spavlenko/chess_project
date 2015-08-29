#include "Transition.h"

Transition::Transition()
{
}

Transition::Transition(TIndex from, TIndex to, Figure::Side actor, Figure::Type victim)
    : m_from(from)
    , m_to(to)
    , m_actor(actor)
    , m_victim(victim)
{
}


QDataStream &operator<<(QDataStream &data, const Transition &transition)
{
    data << transition.m_from << transition.m_to
         << (qint8)transition.m_actor << (qint8)transition.m_victim;

    return data;
}

template<typename T>
QDataStream &operator>>(QDataStream &data, T& val )
{
    int tmp = 0;
    data >> tmp;
    val = static_cast<T>(tmp);

    return data;
}

QDataStream &operator>>(QDataStream &data, Transition &transition)
{
    data >> transition.m_from >> transition.m_to
         >> transition.m_actor >> transition.m_victim;

    return data;
}
