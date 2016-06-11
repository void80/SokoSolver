#include "Direction.h"
#include "Position.h"
#include <iostream>

Direction::Direction(int offsetX, int offsetY, char sign)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;

    this->_back  = this;
    this->_ortho = this;

    this->sign = sign;
}

Direction::~Direction(void)
{
}

int Direction::moveX(void) const
{
    return offsetX;
}
int Direction::moveY(void) const
{
    return offsetY;
}
int Direction::moveX(int oldPos) const
{
    return oldPos + moveX();
}
int Direction::moveY(int oldPos) const
{
    return oldPos + moveY();
}
    
const Direction& Direction::back() const
{
    return *_back;
}
const Direction& Direction::ortho() const
{
    return *_ortho;
}

void Direction::setDirections(const Direction *back, const Direction *ortho)
{
    this->_back   = back;
    this->_ortho  = ortho;
}

void Direction::initDirections(void)
{
    left.setDirections (&right,   &up);
    up.setDirections   ( &down, &left);
    right.setDirections( &left,   &up);
    down.setDirections (   &up, &left);

    dirList.push_back(&left);
    dirList.push_back(&up);
    dirList.push_back(&down);
    dirList.push_back(&right);
}

DirectionList Direction::getAllDirections(void)
{
    return dirList;
}

bool Direction::operator== (const Direction& other) const
{
    return this->offsetX == other.offsetX &&
           this->offsetY == other.offsetY;
}

char Direction::toChar(void) const
{
    return sign;
}

Position Direction::move(const Position &pos) const
{
    return Position(moveY(pos.row), moveX(pos.col));
}

Direction Direction::rotateRight(void) const
{
    return Direction(-offsetY, offsetX, sign);
}
void Direction::print(void) const
{
    std::cout << "X:" << offsetX << " Y:" << offsetY << std::endl;
}
Direction Direction::mirrorX(void) const
{
    return Direction(-offsetX, offsetY, sign);
}
Direction Direction::mirrorY(void) const
{
    return Direction(-offsetX, -offsetY, sign);
}



Direction Direction::left (-1, 0, 'l');
Direction Direction::up   ( 0,-1, 'o');
Direction Direction::right( 1, 0, 'r');
Direction Direction::down ( 0, 1, 'u');
DirectionList Direction::dirList;