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
};

class BufferLayout
{
    public:
        BufferLayout();
        ~BufferLayout();

        void addElem(ElemType type, unsigned int count);

    private:
        std::vector<LayoutElem> elements;
};

#endif // BUFFERLAYOUT_H
