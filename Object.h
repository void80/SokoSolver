#pragma once

// STD
#include <iosfwd>

class Object
{
public:
    Object(char sign = ' ');

private:
    // char m_sign;
	bool m_hasWall;
	bool m_hasPlayer;
	bool m_isPlayerSet;
	bool m_hasGoal;
	bool m_hasBox;

public:
    bool operator==(Object const &other) const;
	char sign() const;

    bool isWallOrBall() const;
    void removeBall();
    void addBall();
    bool hasBall() const;
    bool canAddBall() const;
    bool playerCanStand() const;

public:
    static const Object wall;
    static const Object ball;
    static const Object both;
    static const Object empty;
    static const Object meempty;
    static const Object megoal;
    static const Object goal;
};

inline std::ostream & operator<<(std::ostream &stream, Object const &o)
{
	return stream << o.sign();
}
