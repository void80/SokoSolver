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
    ~Field(void);

    void print(void) const;

    
    int getX(void) const;
    int getY(void) const;
    Position getPosition(void) const;

    int getWidth(void) const;
    int getHeight(void) const;

    const Object &getObject(const Position &pos) const;
    Object &getObject(const Position &pos);
    void insertObject(const Position &pos, Object object);
    
    void removePlayer(const Position &pos);
    void removePlayer(void);
    void addPlayer(const Position &pos);

    int Check(void) const;

    bool isWallLike(const Position &pos, const Direction &noTestDir, int count) const;
    bool isWallLike(const Position &pos, int count, PositionList &usedStones) const;
    bool isPossible(const Position &stonePos) const;
    bool isImpossibleStone(const Position &stonePos) const;
    bool isEdgeOfFourWalls(const Position& pos) const;

    bool isPartOfPattern(const Position &pos, Pattern &pattern) const;
    bool isPartOfUnchangedPattern(const Position &pos, const Pattern &pattern) const;

    bool isWallFull(const Position &stonePos) const;

    PositionList getBallList(bool includeGoal, bool includeBall) const;

    bool isInField(const Position &position) const;

    StepList getWayTo(const Position &pos) const;
    StepList getShortestWayTo(const Position &pos) const;

    bool isSameConfiguration(const Field &other) const;
    bool hasSameBalls(const Field &other) const;
    bool canReachPosition(const Position &pos) const;

    Field createNextField(const Position &stonePos, const Direction &stoneDirection) const;
private:
    int width, height;
    Object *field;

    void initializeField(void);
    int makeIndex(int row, int col) const;
    int makeIndex(const Position &pos) const;

    int posX, posY;

    //static char convertToText(const Object o);

public:
    /*static int moveX(int direction);
    static int moveX(int direction, int oldX);
    static int moveY(int direction);
    static int moveY(int direction, int oldY);*/
};

//typedef std::vector<Field> FieldList;