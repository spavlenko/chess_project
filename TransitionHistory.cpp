#include "TransitionHistory.h"

TransitionHistory::TransitionHistory(QObject *parent) :
    QObject(parent)
{
    _resetIterator();
}

void TransitionHistory::clear()
{
    m_transitions.clear();
    _resetIterator();
}

void TransitionHistory::add(const Transition &transition)
{
    m_transitions.append(transition);
    m_iterator = m_transitions.size();

    emit historyChanged();
}

bool TransitionHistory::isNextAvailable() const
{
    return m_iterator <= m_transitions.size() - 1;
}

bool TransitionHistory::isPrevAvailable() const
{
    return m_iterator > 0;
}

const Transition *TransitionHistory::next()
{
    if(!isNextAvailable())
      return nullptr;

    return &m_transitions.at(m_iterator++);
}

const Transition *TransitionHistory::prev()
{
    if(!isPrevAvailable())
      return nullptr;

    return &m_transitions.at(--m_iterator);
}

void TransitionHistory::_resetIterator()
{
    m_iterator = 0;
    emit historyChanged();
}

QDataStream &operator<<(QDataStream &data, const TransitionHistory &history)
{
    data << history.m_transitions;

    return data;
}


QDataStream &operator>>(QDataStream &data, TransitionHistory &history)
{
    history.clear();
    data >> history.m_transitions;
    history._resetIterator();

    return data;
}
