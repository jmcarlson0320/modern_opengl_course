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
    unsigned int num_floats = elemSize[type] / sizeof(float) * count;
    unsigned int offset = stride;
    struct LayoutElem new_elem = {
        type,
        num_floats,
        offset
    };
    elements.push_back(new_elem);
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
