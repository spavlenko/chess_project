#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>

class Figure : public QObject
{

    Q_OBJECT
public:
    enum Type {
        NONE    = 0,
        KING    = 1,
        QUEEN   = 2,
        KNIGHT  = 3,
        BISHOP  = 4,
        ROOK    = 5,
        PAWN    = 6
    };

    enum Side {
        UNDEF = 0,
        BLACK = 1,
        WHITE = 2
    };
    Q_ENUMS(Type);
    Q_ENUMS(Side);

public:
    explicit Figure(QObject *parent = 0);
    Figure(QObject *parent, Type type, Side side);

    Q_PROPERTY(Side side READ side NOTIFY sideChanged)
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)

    Side side() const;
    Type type() const;

signals:
    void sideChanged(Side side);
    void typeChanged(Type type);

private:
    Type m_type;
    Side m_side;

};

#endif // FIGURE_H
