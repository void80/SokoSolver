#include "Field.h"

#include "defs.h"
#include <iostream>
#include "main.h"

#include "Direction.h"
#include "Position.h"

#include "Object.h"

Field::Field(int width, int height)
{
    this->width  = max(width,  1);
    this->height = max(height, 1);

    field = new Object[this->width * this->height];

    //initale Wand
    initializeField();
}

Field::Field(const Field &other)
{
    width  = other.width;
    height = other.height;
    posX   = other.posX;
    posY   = other.posY;

    field = new Object[this->width * this->height];
    memcpy(field, other.field, sizeof(Object) * this->width * this->height);
}
Field::Field(std::string definition)
{
    this->width = 1;
    this->height = 1;

    int curWidth = 0;
    for (std::string::size_type i = 0; i < definition.size(); i++)
    {
        if (definition[i] == '\n')
        {
            this->height++;
            this->width = max(this->width, curWidth);
            curWidth = 0;
        }
        else
        {
            curWidth++;
        }
    }
    this->width = max(this->width, curWidth);

    field = new Object[this->width * this->height];

    int row = 1;
    int col = 1;
    for (std::string::size_type i = 0; i < definition.size(); i++)
    {
        if (definition[i] == '\n')
        {
            row++;
            col=1;
        }
        else
        {
            insertObject(Position(row, col), Object(definition[i]));
            col++;
        }
    }
    

}


Field::~Field(void)
{
    delete [] field;
}

void Field::initializeField(void)
{
    for(int row = 1; row <= height; row++)
    {
        for(int col = 1; col <= width; col++)
        {
            if (col == 1 || col == width || row == 1 || row == height)
            {
                insertObject(Position(row, col), Object::wall);
            }
            else
            {
                insertObject(Position(row, col), Object::empty);
            }
        }
    }

}

void Field::insertObject(const Position &pos, Object object)
{
    field[makeIndex(pos)] = object;
    if (object == Object::meempty || object == Object::megoal)
    {
       posX = pos.col;
       posY = pos.row;
    }
}

int Field::makeIndex(int row,int col) const
{
    return (row - 1) * this->width + col - 1;
}
int Field::makeIndex(const Position &pos) const
{
    return makeIndex(pos.row, pos.col);
}
void Field::print(void) const
{
    std::cout << std::endl;
    for(int row = 1; row <= height; row++)
    {
        for(int col = 1; col <= width; col++)
        {
            std::cout << getObject(Position(row, col));
        }
        std::cout << std::endl;
    }
}

int Field::getX(void) const
{
    return posX;
}
int Field::getY(void) const
{
    return posY;
}

Object &Field::getObject(const Position &pos)
{
    return field[makeIndex(pos)];
}
const Object &Field::getObject(const Position &pos) const
{
    return field[makeIndex(pos)];
}

int Field::Check(void) const
{
//    int countGoal = 0;
    int countBall = 0;
	
	for (int row = 1; row <= getHeight(); row++)
		for (int col = 1; col <= getWidth(); col++)
		{
            //if(	getObject(Position(row, col)) == goal)
				//countGoal++;
			
			if( getObject(Position(row, col)) == Object::ball)
				countBall++;
		}
	
    return countBall;
}

//prüft, ob das entsprechende Feld Wandähnlich ist. noTestDir wird nicht getestet.
bool Field::isWallLike(const Position &pos, const Direction &noTestDir, int count) const
{
    if (isInField(pos))
    {

        if (getObject(pos) == Object::wall)
            return true;
        
        if (count > 0)
        {
            if (getObject(pos) == Object::ball ||
                getObject(pos) == Object::both)
            {
                //Feld gegenüber von noTestDir
                if (isWallLike(noTestDir.back().move(pos), noTestDir, count - 1))
                {
                    // Links oder Rechts von noTestDir
                    return
                        isWallLike(noTestDir.ortho().move(pos), noTestDir.ortho().back(), count - 1) ||
                        isWallLike(noTestDir.ortho().back().move(pos), noTestDir.ortho(), count - 1);
                }
            }
        }
        return false;	// genug getestet, ist keine wand
    }
    else
    {
        //ausserhalb Feld
        return true;
    }
}


//prüft, ob das entsprechende FeldWallLike ist
bool Field::isWallLike(const Position &pos, int count, PositionList &usedStones) const
{
    if (!isInField(pos))
    {
        return true;
    }

    //Wall like heisst: entweder Wand, oder Ball, der von zwei orthogonalen Seiten Wall likes hat
    if (getObject(pos) == Object::wall)
        return true;

    if (count > 0)
    {
        if (getObject(pos) == Object::ball || getObject(pos) == Object::both)
        {
            // Schon betrachteter Stein?
            if (usedStones.contains(pos))
                return true;

            usedStones.push_back(pos);

            DirectionList dirList = Direction::getAllDirections();
            for (DirectionList::const_iterator dir = dirList.begin();
                 dir != dirList.end();
                 dir++)
            {
                if (isWallLike((*dir)->move(pos), count - 1, usedStones))
                {
                    if (isWallLike((*dir)->ortho().move(pos), count - 1, usedStones) ||
                        isWallLike((*dir)->ortho().back().move(pos), count - 1,usedStones))
                        return true;
                }
            }

        }
    }

    return false;
}

bool Field::isEdgeOfFourWalls(const Position& pos) const
{
    //top Left of Block
    if (pos.col <= getWidth() - 1 && pos.row <= getHeight() - 1)
        if (getObject(pos + Direction::right).isWallOrBall() &&
            getObject(pos + Direction::down).isWallOrBall() &&
            getObject(pos + Direction::right + Direction::down).isWallOrBall())
            return true;
    //top Right of Block
    if (pos.col >= 2 && pos.row <= getHeight() - 1)
        if (getObject(pos + Direction::left).isWallOrBall() &&
            getObject(pos + Direction::down).isWallOrBall() &&
            getObject(pos + Direction::left + Direction::down).isWallOrBall())
            return true;
    //Bottom Left of Block
    if (pos.col <= getWidth() - 1 && pos.row >= 2)
        if (getObject(pos + Direction::right).isWallOrBall() &&
            getObject(pos + Direction::up).isWallOrBall() &&
            getObject(pos + Direction::right + Direction::up).isWallOrBall())
            return true;
    //BottomRight of Block
    if (pos.col >= 2 && pos.row >= 2)
        if (getObject(pos + Direction::left).isWallOrBall() &&
            getObject(pos + Direction::up).isWallOrBall() &&
            getObject(pos + Direction::left + Direction::up).isWallOrBall())
            return true;

    return false;
}

#if 0
bool Field::isWallFull(const Position &stonePos) const
{
    /*
    ##
    #
    #$ <-- Pos
    #
    ##
    */
    /* finde eine U förmige Wand.
    left up und down stehen für die Richtungen, 
    allerdings für alle, d.h.left muss nicht zwangsweise nach links zeigen
    */
    DirectionList dirList = Direction::getAllDirections();
    for (DirectionList::const_iterator pLeft = dirList.begin(); pLeft != dirList.end(); pLeft++)
    {
        Direction left = **pLeft;
        Direction up   = left.ortho();
        Direction down = up.back();

        if (getObject(pos + left) == wall)
        {
            // Links ist eien Wand, Rand des Us finden
            
            // oberer Rand

        
        }
    }
}
bool Field::isPossible(const Position &pos, const Direction &dir) const
{
	// folgendes gilt asl unmöglich :
	//   -------	wobei % für einen WallLike
	//   -  %  -	Platz steht. also eine wand,
	//   - %$  -	oder ein stein, der nicht 
	//   -     -	verschoben werden kann
	//   -------
	return 
        getObject(pos) == Object::both ||
        !isWallLike(pos, dir.back(), 4);
}
#endif
bool Field::isPossible(const Position &stonePos) const
{
    if (isImpossibleStone(stonePos))
        return false;

    DirectionList dirList = Direction::getAllDirections();
    for (DirectionList::const_iterator dir = dirList.begin(); dir != dirList.end(); dir++)
    {
        if (isInField((*dir)->move(stonePos)))
        {
            if (isImpossibleStone((*dir)->move(stonePos)))
                return false;
        }
    }
    
    return true;            
}

bool Field::isImpossibleStone(const Position &stonePos) const
{
    return getObject(stonePos) == Object::ball &&
           ( isEdgeOfFourWalls(stonePos) ||
             isWallLike(stonePos, 5, PositionList()));
}



void Field::removePlayer(const Position &pos)
{
    insertObject(pos,
                 getObject(pos) == Object::megoal ? Object::goal : Object::empty);
}

void Field::removePlayer()
{
    removePlayer(getPosition());
}
Position Field::getPosition() const
{
    return Position(getY(), getX());
}
void Field::addPlayer(const Position &pos)
{
    insertObject(pos,
                 (getObject(pos) == Object::goal || getObject(pos) == Object::both) ? Object::megoal : Object::meempty);
}

int Field::getWidth(void) const
{
    return width;
}
int Field::getHeight(void) const
{
    return height;
}

PositionList Field::getBallList(bool includeGoal, bool includeBall) const
{
    PositionList result;

    for (int row = 1; row <= getHeight(); row++)
    {
        for (int col = 1; col <= getWidth(); col++)
        {
            if ((includeBall && getObject(Position(row, col)) == Object::ball) ||
                (includeGoal && getObject(Position(row, col)) == Object::both))
                result.push_back(Position(row,col));
        }   
    }
    return result;
}

bool Field::isInField(const Position &position) const
{
    return position.row > 0 && position.row <= getHeight() &&
           position.col > 0 && position.col <= getWidth();

}



StepList Field::getWayTo(const Position &pos) const
{
    //Idee:
    //finde einen Weg von aktueller Position zum Ziel
    //probiere alle alle Richtungen aus
    //setzte Wand an eigene Position
    //probiere so erzeugtes Feld zu durchqueren

    // am Ziel?
    if (pos == getPosition())
        return StepList();

    DirectionList dirList = Direction::getAllDirections();
    for (DirectionList::const_iterator dir = dirList.begin();
         dir != dirList.end();
         dir++)
    {
        if (getObject((*dir)->move(getPosition())).playerCanStand())
        {
            Field nextField(*this);
            nextField.addPlayer((*dir)->move(getPosition()));
          //  nextField.print();
            nextField.insertObject(getPosition(), Object::wall);
            
            try
            {
                StepList way = nextField.getWayTo(pos);
                way.push_front(Step(*dir, false));
                return way;
            }
            catch (bool)
            {
                continue;
            }
        }
    }


    throw false; 
}

StepList Field::getShortestWayTo(const Position &pos) const
{
    //Idee:
    //finde einen Weg von aktueller Position zum Ziel
    //probiere alle Richtungen aus
    //setzte Wand an eigene Position
    //probiere so erzeugtes Feld zu durchqueren

    // am Ziel?
    if (pos == getPosition())
        return StepList();

    StepList shortestWay;
    bool found = false;

    DirectionList dirList = Direction::getAllDirections();
    for (DirectionList::const_iterator dir = dirList.begin();
         dir != dirList.end();
         dir++)
    {
        if (getObject((*dir)->move(getPosition())).playerCanStand())
        {
            Field nextField(*this);
            nextField.addPlayer((*dir)->move(getPosition()));
          //  nextField.print();
            nextField.insertObject(getPosition(), Object::wall);
            
            try
            {
                StepList way = nextField.getShortestWayTo(pos);
                way.push_front(Step(*dir, false));
                if (!found || way.size() < shortestWay.size())
                    shortestWay  = way;
                found = true;
            }
            catch (bool)
            {
                continue;
            }
        }
    }

    if (found)
    {
        return shortestWay;
    }

    throw false; 
}

bool Field::isSameConfiguration(const Field &other) const
{
    return hasSameBalls(other) && canReachPosition(other.getPosition());
}

bool Field::hasSameBalls(const Field &other) const
{
    PositionList ownBalls   = getBallList(true, true);
    PositionList otherBalls = other.getBallList(true, true);
    
    if (ownBalls.size() == otherBalls.size())
    {
        for (PositionList::const_iterator i = ownBalls.begin(),
                                          j = otherBalls.begin();
             i != ownBalls.end() && j != otherBalls.end();
             i++, j++)
        {
            if (!(*i == *j))
                return false;
        }

        return true;
    }
    
    return false;    
}

bool Field::canReachPosition(const Position &pos) const
{
    try
    {
        getWayTo(pos);
        return true;
    }
    catch (bool)
    {
        
    }

    return false;
}

Field Field::createNextField(const Position &stonePos, const Direction &stoneDirection) const
{
    Field result(*this);

    //Stein verschieben
    result.getObject(stonePos).removeBall();
    result.getObject(stonePos + stoneDirection).addBall();
    // Spieler verschieben
    result.removePlayer();
    result.addPlayer(stonePos);

    return result;
}