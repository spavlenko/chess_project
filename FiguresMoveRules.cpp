#include "FiguresMoveRules.h"
#include "Constants.h"
#include "BoardController.h"

#include <cstdlib>
#include <assert.h>

namespace  {
    typedef std::pair<int, int> TCoordinate;

    TCoordinate _indexToCoord(int index)
    {
        int row = index / Constants::board_size;
        int col = index % Constants::board_size;

        return std::make_pair(row, col);
    }

    int _coordToIndex(int row, int col)
    {
        return row * Constants::board_size + col;
    }

    int _coordToIndex(const TCoordinate& coord)
    {
       return _coordToIndex(coord.first, coord.second);
    }

    bool isMoveValidPawn(Figure::Side side, const TCoordinate& from, const TCoordinate& to, bool attack)
    {
        bool direction_down = Figure::BLACK == side;

        if(direction_down && _coordToIndex(to) < _coordToIndex(from))
            return false;

        int x_disp = std::abs(from.first - to.first);
        int y_disp = std::abs(from.second - to.second);

        if(attack)
        {
            if(x_disp == 1 && y_disp == 1)
                return true;
            else
                return false;
        }
        bool is_first_move = from.first == 1 || from.first == 6;
        int max_x_disp = is_first_move ? 3 : 2;

        return (x_disp < max_x_disp) && (y_disp == 0);
    }

    bool isMoveValidRook(const TCoordinate& from, const TCoordinate& to)
    {
        return to.first == from.first ||
                to.second == from.second;
    }

    bool isMoveValidBishop(const TCoordinate& from, const TCoordinate& to)
    {
        return std::abs(from.first - to.first) ==
                std::abs(from.second - to.second);
    }

    bool isMoveValidKnight(const TCoordinate& from, const TCoordinate& to)
    {
        int x_disp = std::abs(from.first - to.first);
        int y_disp = std::abs(from.second - to.second);

        return (x_disp == 2 && y_disp == 1) ||
                (x_disp == 1 && y_disp == 2);
    }

    bool isMoveValidQueen(const TCoordinate& from, const TCoordinate& to)
    {
        return isMoveValidRook(from, to) ||
                 isMoveValidBishop(from, to);
    }

    bool isMoveValidKing(const TCoordinate& from, const TCoordinate& to)
    {
        int x_disp = std::abs(from.first - to.first);
        int y_disp = std::abs(from.second - to.second);

        return x_disp < 2 && y_disp < 2;
    }

    bool isPositionAccessibleRook(int from, int to, const BoardController &board)
    {
        auto coord_to = _indexToCoord(to);
        auto coord_from = _indexToCoord(from);

        auto start = std::make_pair(std::min(coord_from.first, coord_to.first),
                                    std::min(coord_from.second, coord_to.second));

        auto end = std::make_pair(std::max(coord_from.first, coord_to.first),
                                  std::max(coord_from.second, coord_to.second));

        for(int i = start.first; i < end.first; ++i)
        {
            auto type = board.figureAt(_coordToIndex(i, start.second))->type();
            if( type != Figure::NONE && type != Figure::ROOK)
                return false;
        }

        for(int i = start.second; i < end.second; ++i)
        {
            auto type = board.figureAt(_coordToIndex(start.first, i))->type();
            if( type != Figure::NONE && type != Figure::ROOK)
                return false;
        }

        return true;
    }

    bool isPositionAccessibleBishop(int from, int to, const BoardController &board)
    {
        auto start = std::min(from, to);
        auto end =  std::max(from, to);

        auto coord_to = _indexToCoord(end);
        auto coord_from = _indexToCoord(start);

        int step = coord_from.second - coord_to.second + Constants::board_size;

        for(; start < end; start += step)
            if(board.figureAt(start)->type() != Figure::NONE && board.figureAt(start)->type() != Figure::BISHOP)
                return false;

        return true;
    }

    bool isPositionAccessibleQueen(int from, int to, const BoardController &board)
    {
        return isPositionAccessibleRook(from, to, board) ||
                isPositionAccessibleBishop(from, to, board);
    }

}


bool isMoveValid(Figure::Type type, Figure::Side side, int from, int to, bool attack)
{
    auto coord_to = _indexToCoord(to);
    auto coord_from = _indexToCoord(from);

    switch (type) {
    case Figure::PAWN:
        return isMoveValidPawn(side, coord_from, coord_to, attack);
    case Figure::ROOK:
        return isMoveValidRook(coord_from, coord_to);
    case Figure::BISHOP:
        return isMoveValidBishop(coord_from, coord_to);
    case Figure::KNIGHT:
        return isMoveValidKnight(coord_from, coord_to);
    case Figure::QUEEN:
        return isMoveValidQueen(coord_from, coord_to);
    case Figure::KING:
        return isMoveValidKing(coord_from, coord_to);

    default:
        assert(!"Should not happen");
        return false;
    }
}

bool isPositionAccessible(Figure::Type type, int from, int to, const BoardController &board)
{
    switch (type) {
    case Figure::KNIGHT:
    case Figure::PAWN:
    case Figure::KING:
        return true;

    case Figure::ROOK:
        return isPositionAccessibleRook(from, to, board);

    case Figure::BISHOP:
         return isPositionAccessibleBishop(from, to, board);

    case Figure::QUEEN:
         return isPositionAccessibleQueen(from, to, board);

    default:
        assert(!"Should not happen");
        return false;
    }
}
