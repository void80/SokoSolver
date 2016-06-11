#pragma once

class Field;
class Direction;
class FieldList;
#include "StepList.h"
class PositionList;

class Solution
{
private:
    typedef enum {undefined, impossible, nextStep, tooMuchSteps, similar} State;

public:
    Solution(int maxSteps);
    virtual ~Solution(void);

public:

    void increaseSteps(void);
    unsigned long getSteps(int index) const;
    void show(void) const;
    int find(int iStep, const Direction &dir, Field field);
    StepList find(int remainingSteps, Field field, FieldList &fieldHistory);
    StepList tryStones(int remaininSteps, const Field &field, const PositionList &stoneList, FieldList &fieldList);

    int optimize(int iStep, Field &field);
    int move(int iStep, const Direction &dir,Field &field);
    void undoStep(int iStep);
    void printStats(int step) const;
private:
    void showState(State state) const;
    unsigned long steps[2];  
    char *way;
    char *stone;
    char *cPosX;
    char *cPosY;

};
