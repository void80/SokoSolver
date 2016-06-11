#pragma once

class Object
{
public:
    Object(void);
    Object(char sign);
    Object(const Object &other);
    ~Object(void);

private:
    char sign;

public:
    bool operator== (const Object &other) const;
    operator char() const;

    bool isWallOrBall(void) const;
    void removeBall(void);
    void addBall(void);
//    void addPlayer(void);
    bool hasBall(void) const;
    bool canAddBall(void) const;
    bool playerCanStand(void) const;

public:
    static const Object wildcard;
    static const Object anyBall;

    static const Object wall;
    static const Object ball;
    static const Object both;
    static const Object empty;
    static const Object meempty;
    static const Object megoal;
    static const Object goal;
};
