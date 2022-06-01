#include "BufferLayout.h"

#include <vector>

static unsigned int elemSize[NUM_ELEM_TYPES] = {
    [FLOAT] = sizeof(float),
    [VEC2] = sizeof(float) * 2,
    [VEC3] = sizeof(float) * 3,
    [VEC4] = sizeof(float) * 4,
};

BufferLayout::BufferLayout()
{
    stride = 0;
}

BufferLayout::~BufferLayout()
{
}

void BufferLayout::addElem(ElemType type, unsigned int count)
{
    elements.push_back({type, count});
    stride += elemSize[type] * count;
}
