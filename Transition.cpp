#include "Transition.h"

Transition::Transition()
{
}

Transition::Transition(TIndex from, TIndex to, Figure::Side victim_side, Figure::Type victim_type)
    : m_from(from)
    , m_to(to)
    , m_victim_side(victim_side)
    , m_victim_type(victim_type)
{
}

QDataStream &operator<<(QDataStream &data, const Transition &transition)
{
    data << transition.m_from << transition.m_to
         << (qint8)transition.m_victim_side << (qint8)transition.m_victim_type;

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
         >> transition.m_victim_side >> transition.m_victim_type;

    return data;
}
