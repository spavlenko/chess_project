#ifndef FIGURESMOVERURES_H
#define FIGURESMOVERURES_H

#include "Figure.h"

#include <QSet>

class BoardController;

bool isMoveValid(Figure::Type type, Figure::Side side, int from, int to, bool attack);

bool isPositionAccessible(Figure::Type type, int from, int to, const BoardController &board);

#endif // FIGURESMOVERURES_H
