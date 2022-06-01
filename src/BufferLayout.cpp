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
    unsigned int offset = stride;
    elements.push_back({type, count, offset});
    stride += elemSize[type] * count;
}

std::vector<LayoutElem> BufferLayout::getElements()
{
    return elements;
}

unsigned int BufferLayout::getStride()
{
    return stride;
}
