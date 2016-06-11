#include "Pattern.h"
#include "FieldElement.h"
#include "Position.h"//am.
#include "PositionList.h" //am.

Pattern::Pattern(std::string definition)
:Field (definition)
{
}

void Pattern::rotateLeft(void)
{
    //for(iterator element = begin(); element != end(); element++)
    //{
    //    element->offset = element->offset.rotateLeft();
    //}
}

Pattern Pattern::getEdgePattern(void)
{
    static Pattern pattern(
                "#O?\n"
				//"#?$\n"
				"# O\n"
				"###\n");

    return pattern;
}
Pattern Pattern::getEdgePatternOneLineTwoEmpty(void) //am. 26.05.07
{
    static Pattern pattern(
				"#O?\n"
				"# O\n"
				"# O\n"
                "##?\n");

    return pattern;
}

Pattern Pattern::getBigEdgePattern(void)
{
    static Pattern pattern(
                //"#$O?\n"
				"#OO?\n"
				//"#??O\n"
				"#  O\n"
                "####\n");

    return pattern;
}

bool Pattern::existsInField(const Field &field, const Position &posInField) const
{
    
    PositionList ballList = getBallList(field.getObject(posInField) == Object::both,
                                        field.getObject(posInField) == Object::ball,
                                        true,true);
    
    for (PositionList::const_iterator ball = ballList.begin(); ball != ballList.end(); ball++)
    {
        //if (existsInField(*ball, field, posInField))
		if (existsInField(*ball, field, posInField, ballList.size ())) //am. 26.05.07
        {
            return true;
        }
    }
    return false;
}

bool Pattern::existsInField(const Position &posInPattern,const Field &field, const Position &posInField, 
	int nBallCountMax /*= -1*/) const //am. 26.05.07
{
    return existsInField(posInPattern, field, posInField, false, false, false, nBallCountMax)
        || existsInField(posInPattern, field, posInField, false, false, true, nBallCountMax)
        || existsInField(posInPattern, field, posInField, false, true,  false, nBallCountMax)
        || existsInField(posInPattern, field, posInField, false, true,  true, nBallCountMax)
        || existsInField(posInPattern, field, posInField, true,  false, false, nBallCountMax)
        || existsInField(posInPattern, field, posInField, true,  false, true, nBallCountMax)
        || existsInField(posInPattern, field, posInField, true,  true,  false, nBallCountMax)
        || existsInField(posInPattern, field, posInField, true,  true,  true, nBallCountMax);
}


bool Pattern::existsInField(const Position &posInPattern,const Field &field, const Position &posInField, bool mirrorX, bool mirrorY, bool rotate, 
	int nBallCountMax /*= -1*/) const//am. 26.05.07
{
    for (int row = 1; row <= this->getHeight(); row ++)
        for (int col = 1; col <= this->getWidth(); col ++)
        {
            Position positionInPattern(row, col);
            Direction vector = positionInPattern-posInPattern;
            
            if (rotate)  vector = vector.rotateRight();
            if (mirrorX) vector = vector.mirrorX();
            if (mirrorY) vector = vector.mirrorY();

            if (field.isInField(posInField + vector))
            {
				//am. 26.05.07
				if (nBallCountMax != -1)
				{
					if (field.getObject(posInField + vector) == Object::ball)
						nBallCountMax--;
				}
				//end am. 26.05.07
                //if (!compareObject(getObject(positionInPattern), field.getObject(posInField + vector)))
				if (!compareObject(getObject(positionInPattern), field.getObject(posInField + vector), nBallCountMax))
                    return false;
            }
            else
            {
                return false;
            }
        }
    return true;
}

bool Pattern::compareObject(Object our, Object other,
	int nBallCount /*= -1*/) const //am. 26.05.07
{
    //return our == other || our == Object::wildcard 
    //    || (our == Object::anyBall && (other == Object::ball || other == Object::both));
	return ( our == other || our == Object::wildcard 
        || (our == Object::anyBall && (other == Object::ball || other == Object::both)) ) && (nBallCount > 0 || nBallCount == -1);
}

PositionList Pattern::getBallList(bool includeGoal, bool includeBall, bool includeWildcard, bool includeAnyBall) const
{
    PositionList result;

    for (int row = 1; row <= getHeight(); row++)
        for (int col = 1; col <= getWidth(); col++)
        {
            if ((includeBall     && getObject(Position(row, col)) == Object::ball)
             || (includeGoal     && getObject(Position(row, col)) == Object::both)
             || (includeWildcard && getObject(Position(row, col)) == Object::wildcard)
             || (includeAnyBall  && getObject(Position(row, col)) == Object::anyBall))

                result.push_back(Position(row,col));
        }   
    return result;
}