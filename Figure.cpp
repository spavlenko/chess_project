#include "Figure.h"


Figure::Figure(QObject *parent) :
    QObject(parent),
    m_type(Type::NONE),
    m_side(Side::WHITE)
{

}

Figure::Figure(QObject *parent, Figure::Type type, Figure::Side side):
    QObject(parent),
    m_type(type),
    m_side(side)
{

}

Figure::Side Figure::side() const
{
    return m_side;
}


Figure::Type Figure::type() const
{
    return m_type;
}