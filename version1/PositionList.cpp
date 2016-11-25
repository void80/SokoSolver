#include "PositionList.h"

#include "Position.h"

bool PositionList::contains(const Position &pos) const
{
    for (const_iterator element = begin(); element != end(); element++)
    {
        if (pos == *element)
            return true;
    }
    return false;
}