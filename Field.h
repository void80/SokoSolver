#pragma once

class Direction;

#include "Position.h"
#include "StepList.h"
#include "PositionList.h"
class Pattern;
class Object;

class Field
{
public:
/*    typedef enum{ball    = '$', 
                 goal    = '.',
                 both    = '*',
                 wall    = '#',
                 empty   = ' ',
                 megoal  = ':',
                 meempty = '@'} Object;*/

public:
    Field(int width, int height);
    Field(const Field &field);
    Field(std::string definition);
    ~Field();

    void print() const;

    
    int getX() const;
    int getY() const;
    Position getPosition() const;

    int getWidth() const;
    int getHeight() const;

    const Object &getObject(Position const &pos) const;
    Object &getObject(Position const &pos);
    void insertObject(Position const &pos, Object object);
    
    void removePlayer(const Position &pos);
    void removePlayer();
    void addPlayer(Position const &pos);

    int Check() const;

    bool isWallLike(Position const &pos, Direction const &noTestDir, int count) const;
    bool isWallLike(Position const &pos, int count, PositionList &usedStones) const;
    bool isPossible(Position const &stonePos) const;
    bool isImpossibleStone(Position const &stonePos) const;
    bool isEdgeOfFourWalls(Position const &pos) const;

    // bool isPartOfPattern(const Position &pos, Pattern &pattern) const;
    // bool isPartOfUnchangedPattern(const Position &pos, const Pattern &pattern) const;

    bool isWallFull(Position const &stonePos) const;

    PositionList getBallList(bool includeGoal, bool includeBall) const;

    bool isInField(Position const &position) const;

    StepList getWayTo(Position const &pos) const;
    StepList getShortestWayTo(Position const &pos) const;

    bool isSameConfiguration(Field const &other) const;
    bool hasSameBalls(Field const &other) const;
    bool canReachPosition(Position const &pos) const;

    Field createNextField(Position const &stonePos, Direction const &stoneDirection) const;
private:
    int width, height;
    Object *field;

    void initializeField();
    int makeIndex(int row, int col) const;
    int makeIndex(const Position &pos) const;

    int posX, posY;


};
