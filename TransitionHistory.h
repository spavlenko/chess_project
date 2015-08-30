#ifndef TRANSITIONHISTORY_H
#define TRANSITIONHISTORY_H

#include "Transition.h"

#include <QObject>
#include <QList>
#include <QDataStream>

class TransitionHistory : public QObject
{
    Q_OBJECT
public:
    explicit TransitionHistory(QObject *parent = 0);

    void clear();
    void add(const Transition& transition);

    bool isNextAvailable() const;
    bool isPrevAvailable() const;

    const Transition* next();
    const Transition* prev();

private:
    void _resetIterator();

    friend  QDataStream &operator<<(QDataStream &data, const TransitionHistory &history);
    friend  QDataStream &operator>>(QDataStream &data, TransitionHistory &history);

private:
    QList<Transition> m_transitions;
    int m_iterator = 1;
};

 QDataStream &operator<<(QDataStream &data, const TransitionHistory &history);
 QDataStream &operator>>(QDataStream &data, TransitionHistory &history);

#endif // TRANSITIONHISTORY_H
