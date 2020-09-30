#include "IndexBuffer.h"
#include<GL/glew.h>
#include <Error.h>

IndexBuffer::IndexBuffer(m_BufferView buffer)
    :id(0)
{
    m_count = buffer.byteLength;
    this->m_buffer= buffer;
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(buffer.target, id));
    GLCALL(glBufferData(buffer.target,
        buffer.byteLength,
        buffer.buffer,
        GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &id));
}
void IndexBuffer :: bindIndex() const{
    GLCALL(glBindBuffer(this->m_buffer.target, id));
    //GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_count * sizeof(unsigned int), indices));
}
void IndexBuffer::unBindIndex() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
void IndexBuffer::deleteIndex() const {
    GLCALL(glDeleteBuffers(1, &id));
}
unsigned int IndexBuffer::get_ibo_id() const {
    return id;
}
