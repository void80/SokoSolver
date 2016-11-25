#include "FieldElement.h"

FieldElement::FieldElement(Object object, Direction &_offset) 
: offset(_offset)
{
    this->object = object;
}

FieldElement::~FieldElement(void)
{
}
