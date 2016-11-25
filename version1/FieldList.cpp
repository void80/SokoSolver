#include "FieldList.h"
#include "defs.h"
#include <iostream>

/*FieldList1::FieldList1(void)
{
}

FieldList1::~FieldList1(void)
{
}*/

bool FieldList::containsSimilarField(const Field &field) const
{
    for (const_iterator i = begin();
         i != end();
         i++)
    {
        if (field.isSameConfiguration(*i))
        {
            return true;
        }
    }

    return false;
}