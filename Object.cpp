
// PROJECT
#include "Object.h"

// STD
#include <utility>
#include <exception>
#include <string>


namespace
{
    bool hasWall(char sign);
    bool hasPlayer(char sign);
    bool hasGoal(char sign);
    bool hasBox(char sign);
} // OF anonymous NS


static char const WALL          = '#';
static char const BOX			= '$';
static char const BOX_GOAL		= '*';
static char const EMPTY			= ' ';
static char const PLAYER		= '@';
static char const PLAYER_GOAL	= ':';
static char const GOAL			= '.';


Object::Object(char sign)
    : m_hasWall(hasWall(sign))
    , m_hasPlayer(hasPlayer(sign))
    , m_isPlayerSet(false)
    , m_hasGoal(hasGoal(sign))
    , m_hasBox(hasBox(sign))
{
}


bool Object::operator==(Object const &other) const
{
    return m_hasWall == other.m_hasWall
        && m_hasPlayer == other.m_hasPlayer
        && m_isPlayerSet == other.m_isPlayerSet
        && m_hasGoal == other.m_hasGoal
        && m_hasBox == other.m_hasBox
    ;
}

bool Object::isWallOrBall() const
{
    return m_hasWall || m_hasBox;
}

void Object::removeBall()
{
    m_hasBox = false;
}

void Object::addBall()
{
    m_hasBox = true;
}
bool Object::hasBall() const
{
    return m_hasBox;
}
bool Object::canAddBall() const
{
    return !m_hasWall && !m_hasPlayer && !m_hasBox;
}

bool Object::playerCanStand() const
{
    return !m_hasWall && !m_hasBox;
}

char Object::sign() const
{
	if(m_hasWall)
	{
		return WALL;
	}
	else
	{
		if(m_hasGoal)
		{
			if(m_hasPlayer)
			{
				return PLAYER_GOAL;
			}
            else if(m_hasBox)
            {
                return BOX_GOAL;
            }
            else
            {
                return GOAL;
            }
		}
		else
		{
            if(m_hasPlayer)
            {
                return PLAYER;
            }
            else
            {
                return EMPTY;
            }
		}
	}
}

const Object Object::wall   (WALL);
const Object Object::ball   (BOX);
const Object Object::both   (BOX_GOAL);
const Object Object::empty  (EMPTY);
const Object Object::meempty(PLAYER);
const Object Object::megoal (PLAYER_GOAL);
const Object Object::goal   (GOAL);


namespace 
{

    bool hasWall(char sign)
    {
        return sign == WALL;
    }

    bool hasPlayer(char sign)
    {
        return sign == PLAYER || sign == PLAYER_GOAL;
    }
    
    bool hasGoal(char sign)
    {
        return sign == GOAL || sign == PLAYER_GOAL || sign == BOX_GOAL;
    }
    
    bool hasBox(char sign)
    {
        return sign == BOX || sign == BOX_GOAL;
    }

} // OF anonymous NS



