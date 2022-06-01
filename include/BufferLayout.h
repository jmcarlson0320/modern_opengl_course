#ifndef BUFFERLAYOUT_H
#define BUFFERLAYOUT_H

#include <vector>

enum ElemType {
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    NUM_ELEM_TYPES
};

struct LayoutElem {
    ElemType type;
    unsigned int count;
    unsigned long int offset;
};

class BufferLayout
{
    public:
        BufferLayout();
        ~BufferLayout();

        void addElem(ElemType type, unsigned int count);
        std::vector<LayoutElem> getElements();
        unsigned int getStride();

    private:
        std::vector<LayoutElem> elements;
        unsigned int stride;
};

#endif // BUFFERLAYOUT_H
