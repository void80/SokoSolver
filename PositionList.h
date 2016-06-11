#pragma once

#include "Position.h"
#include <vector>

class PositionList : public std::vector<Position>
{
public:
    bool contains(const Position &pos) const;
    
};
