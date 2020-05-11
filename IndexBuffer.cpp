#include "IndexBuffer.h"
#include<GL/glew.h>
#include <Error.h>

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
{
    m_count = count;
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GLCALL(glGenBuffers(1, &m_renderer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW));
}
IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_renderer_id));
}
void IndexBuffer::bindIndex() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}
void IndexBuffer::unBindIndex() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
