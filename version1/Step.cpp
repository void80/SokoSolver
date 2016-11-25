#include "Step.h"

#include <iostream>
#include "Direction.h"


Step::Step(const Direction *direction, bool stone)
{
    this->direction = direction;
    this->stone = stone;
}

Step::~Step(void)
{
}


void Step::print(void) const
{
    std::cout << direction->toChar() << (stone ? "*" : "") << ' ';
}