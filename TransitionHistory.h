#ifndef TRANSITIONHISTORY_H
#define TRANSITIONHISTORY_H

#include "Transition.h"

#include <QObject>
#include <QLinkedList>
#include <QDataStream>

class TransitionHistory : public QObject
{
    Q_OBJECT
public:
    explicit TransitionHistory(QObject *parent = 0);

    void clear();
    void add(const Transition& transition);

    const Transition* next();
    const Transition* prev();

private:
    void _initIterator();
    friend  QDataStream &operator<<(QDataStream &data, const TransitionHistory &history);
    friend  QDataStream &operator>>(QDataStream &data, TransitionHistory &history);

private:
    QLinkedList<Transition> m_transitions;
    QLinkedList<Transition>::iterator m_iterator;
};

 QDataStream &operator<<(QDataStream &data, const TransitionHistory &history);
 QDataStream &operator>>(QDataStream &data, TransitionHistory &history);

#endif // TRANSITIONHISTORY_H
