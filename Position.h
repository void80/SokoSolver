#pragma once

#include <vector>
class Direction;

class Position
{
public:
    Position(int row, int col);
    ~Position(void);

public:
    bool operator== (const Position &other) const;
    Position operator+ (const Direction &dir) const;
    Direction operator- (const Position &other) const;
public:
    int row, col;

};