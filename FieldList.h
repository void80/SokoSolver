#pragma once

#include <list>
#include "Field.h"

class FieldList : public std::list<Field>
{
public:
   // FieldList(void);
   // ~FieldList(void);
public:
    bool containsSimilarField(const Field &field) const;
};
