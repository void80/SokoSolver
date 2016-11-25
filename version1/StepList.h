#pragma once

#include <list>
#include "Step.h"

class StepList : public std::list<Step>
{
public:
    void print(void) const;
    void operator += (const StepList &other);
};
