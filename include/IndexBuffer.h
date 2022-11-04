#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
    public:
        IndexBuffer();
        ~IndexBuffer();

        void init(unsigned int *data, unsigned int num_elem);
        void bind();
        void unbind();

        unsigned int getIndexCount();

    private:
        GLuint bufferID;
        unsigned int num_indices;
};

#endif // INDEXBUFFER_H
