#include "Position.h"
#include "Direction.h"

Position::Position(int row, int col)
{
    this->row = row;
    this->col = col;
}

Position::~Position(void)
{
}

bool Position::operator== (const Position &other) const
{
    return row == other.row && col == other.col;
}

Position Position::operator+ (const Direction &dir) const
{
    return dir.move(*this);
}

Direction Position::operator- (const Position &other) const
{
    return Direction(col - other.col, row - other.row, 'x');
}