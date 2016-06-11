#pragma once

#include <vector>

class Direction;
typedef std::vector<Direction *> DirectionList;
class Position;

class Direction
{
public:
    Direction(int offsetX, int offsetY, char sign);
    ~Direction(void);
public:
    int moveX(void) const;
    int moveY(void) const;
    int moveX(int oldPos) const;
    int moveY(int oldPos) const;
    
    Position move(const Position &pos) const;

    const Direction& back() const;
    const Direction& ortho() const;

    char toChar(void) const;

    Direction rotateRight(void) const;
    Direction mirrorX(void) const;
    Direction mirrorY(void) const;

    void print(void) const;

public:
    static Direction left;
    static Direction right;
    static Direction up;
    static Direction down;

    static DirectionList getAllDirections(void);

    static void initDirections(void);

    bool operator== (const Direction& other) const;
private:
    const Direction *_back;
    const Direction *_ortho;

    int offsetX, offsetY;
    char sign;

    void setDirections(const Direction *back, const Direction *ortho);
    static DirectionList dirList;
};
