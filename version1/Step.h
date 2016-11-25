#pragma once

#include <vector>
class Direction;

class Step
{
public:
    Step(const Direction *direction, bool stone);
    ~Step(void);
public:
    void print(void) const;

private:
    const Direction *direction;
    bool stone;
};

//typedef std::vector<Step> StepList;