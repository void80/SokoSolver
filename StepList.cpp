#include "StepList.h"

#include "Step.h"

#include <iostream>

void StepList::print(void) const
{
    if (! empty())
    {
        for (const_iterator i = this->begin();
             i != this->end();
             i++)
        {
            i->print();
        }
    }
    else
    {
        std::cout << "empty";
    }

    std::cout << std::endl;
}

void StepList::operator+= (const StepList &other)
{
    for (const_iterator i = other.begin();
         i != other.end();
         i++)
    {
        push_back(*i);
    }
}