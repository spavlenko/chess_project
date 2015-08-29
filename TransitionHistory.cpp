#include "TransitionHistory.h"

TransitionHistory::TransitionHistory(QObject *parent) :
    QObject(parent)
{
}

void TransitionHistory::clear()
{
    m_transitions.clear();
    _initIterator();
}

void TransitionHistory::add(const Transition &transition)
{
    m_transitions.append(transition);

    if(m_transitions.size() == 1)
       _initIterator();
}

const Transition *TransitionHistory::next()
{
    if(m_iterator == m_transitions.end())
      return nullptr;

    auto res = &(*m_iterator);
    ++m_iterator;

    return res;
}

const Transition *TransitionHistory::prev()
{
    if(m_iterator == m_transitions.begin())
      return nullptr;

    auto res = &(*m_iterator);
    ++m_iterator;

    return res;
}

void TransitionHistory::_initIterator()
{
     m_iterator = m_transitions.begin();
}


QDataStream &operator<<(QDataStream &data, const TransitionHistory &history)
{
    data << history.m_transitions;

    return data;
}


QDataStream &operator>>(QDataStream &data, TransitionHistory &history)
{
    data >> history.m_transitions;
    history._initIterator();

    return data;
}
