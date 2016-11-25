#pragma once

#include "Field.h"
#include "Direction.h"

#include <vector>

#include "Object.h"

class FieldElement
{
public:
    FieldElement(Object object,Direction &offset);
    ~FieldElement(void);
public:
    Object object;
    Direction offset;
};
