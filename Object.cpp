#include "Object.h"

Object::Object(void)
{
    this->sign = ' ';
}

Object::Object(char sign)
{
    this->sign = sign;

    switch (sign)
    {
    case '#':
    case ' ':
    case '.':
    case '@':
    case ':':
    case '*':
    case '$':
        break;

    case '?':
    case 'O':
        break;
    default:
        throw sign;

    }

}
Object::Object(const Object &other)
{
    this->sign = other.sign;
}

Object::~Object(void)
{

}

bool Object::operator== (const Object &other) const
{
    return sign == other.sign;
}

bool Object::isWallOrBall(void) const
{
    return *this == wall || *this == ball || *this == both;
}

Object::operator char() const
{
    return sign;
}

void Object::removeBall(void)
{
    *this = (*this == both ? goal : empty);
}

void Object::addBall(void)
{
    *this = (*this == goal || *this == megoal ? both : ball);
}
bool Object::hasBall(void) const
{
    return *this == ball || *this == both;
}

bool Object::canAddBall(void) const
{
    return *this == empty || *this == goal;
}

bool Object::playerCanStand(void) const
{
    return *this == empty || *this == meempty || *this == goal || *this == megoal;
}


const Object Object::wall   ('#');
const Object Object::ball   ('$');
const Object Object::both   ('*');
const Object Object::empty  (' ');
const Object Object::meempty('@');
const Object Object::megoal (':');
const Object Object::goal   ('.');

const Object Object::wildcard ('?');
const Object Object::anyBall  ('O');