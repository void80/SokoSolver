#pragma once

#include <vector>
#include "Field.h"//am.
#include "PositionList.h"

class Position;

class Pattern : public Field //am.
{
    Pattern(std::string definition);
public:
    void rotateLeft(void);
    bool existsInField(const Field &field, const Position &posInField) const;
    bool existsInField(const Position &posInPattern,const Field &field, const Position &posInField, 
		int nBallCountMax = -1) const; //am. 26.05.07
    bool existsInField(const Position &posInPattern,const Field &field, const Position &posInField, bool mirrorX, bool mirrorY, bool rotate,
		int nBallCountMax = -1) const; //am. 26.05.07

    bool compareObject(Object one, Object other,
		int nBallCountMax = -1) const; //am. 26.05.07

    PositionList getBallList(bool includeGoal, bool includeBall, bool includeWildcard, bool includeAnyBall) const;
public:
    static Pattern getEdgePattern(void);
	static Pattern getEdgePatternOneLineTwoEmpty(void); //am. 26.05.07
    static Pattern getBigEdgePattern(void);
};
