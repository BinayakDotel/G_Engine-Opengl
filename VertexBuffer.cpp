#include <VertexBuffer.h>
#include<GL/glew.h>
#include <Error.h>
#include <Vertex.h>
#include <print.h>

VertexBuffer::VertexBuffer(const void* vertices, unsigned int size) {
    GLCALL(glGenBuffers(1, &m_renderer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_renderer_id));
}
void VertexBuffer::bindVertex(const void* vertices, unsigned int size) const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices));
}
void VertexBuffer::unBindVertex() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}