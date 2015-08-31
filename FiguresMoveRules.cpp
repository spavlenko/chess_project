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
        bool is_first_move = from.first == Constants::black_second_row ||
                             from.first == Constants::white_second_row;

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
        bool is_diagonal_valid = isMoveValidBishop(from, to);
        bool is_parralel_valid = isMoveValidRook(from, to);
        return (is_diagonal_valid || is_parralel_valid) &&
               !(is_diagonal_valid && is_parralel_valid);
    }

    bool isMoveValidKing(const TCoordinate& from, const TCoordinate& to)
    {
        int x_disp = std::abs(from.first - to.first);
        int y_disp = std::abs(from.second - to.second);

        return x_disp < 2 && y_disp < 2;
    }

    bool isPositionAccessibleParallel(int from, int to, const BoardController &board, Figure::Type type)
    {
        auto coord_to = _indexToCoord(to);
        auto coord_from = _indexToCoord(from);

        auto start = std::make_pair(std::min(coord_from.first, coord_to.first),
                                    std::min(coord_from.second, coord_to.second));

        auto end = std::make_pair(std::max(coord_from.first, coord_to.first),
                                  std::max(coord_from.second, coord_to.second));

        for(int i = start.first; i < end.first; ++i)
        {
            int index =_coordToIndex(i, start.second);
            auto f_type = board.figureAt(index)->type();
            if( f_type != Figure::NONE && f_type != type  && index != to)
                return false;

        }

        for(int i = start.second; i < end.second; ++i)
        {

            int index =_coordToIndex(i, start.second);
            auto f_type = board.figureAt(index)->type();
            if( f_type != Figure::NONE && f_type != type && index != to)
                return false;
        }

        return true;
    }

    bool isPositionAccessibleDiagonal(int from, int to, const BoardController &board, Figure::Type type)
    {
        int start = std::min(from, to);
        int end =  std::max(from, to);

        auto s_coord = _indexToCoord(start);
        auto e_coord = _indexToCoord(end);

        bool moving_right = s_coord.second < e_coord.second;

        int step = Constants::board_size + (moving_right ? 1 : -1);

        for(; start < end; start += step)
            if(board.figureAt(start)->type() != Figure::NONE
                    && board.figureAt(start)->type() != type
                    && start != to)
                return false;

        return true;
    }

    bool isPositionAccessibleQueen(int from, int to, const BoardController &board)
    {
        return isPositionAccessibleDiagonal(from, to, board, Figure::QUEEN) ||
                isPositionAccessibleParallel(from, to, board, Figure::QUEEN);
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
        return isPositionAccessibleParallel(from, to, board, Figure::ROOK);

    case Figure::BISHOP:
         return isPositionAccessibleDiagonal(from, to, board, Figure::BISHOP);

    case Figure::QUEEN:
         return isPositionAccessibleQueen(from, to, board);

    default:
        assert(!"Should not happen");
        return false;
    }
}
