#include <VertexBuffer.h>
#include<GL/glew.h>
#include <Error.h>
#include <Vertex.h>
#include <print.h>

VertexBuffer::VertexBuffer(m_BufferView buffer){
    this->m_buffer= buffer;
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(m_buffer.target, this->id));
    
    GLCALL(glBufferData(m_buffer.target,
            m_buffer.byteLength,
            m_buffer.buffer,
            GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &id));
}
/*
void VertexBuffer::bindVertex(m_BufferView m_buffer) const {
    GLCALL(glBindBuffer(m_buffer.target, vbo_id));
    //GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices));
}*/
void VertexBuffer::bindVertex() const {
    GLCALL(glBindBuffer(this->m_buffer.target, this->id));
    /*GLCALL(glBufferSubData(buffer_data.target,
        0, 
        buffer_data.byteLength,
        &buffer_data.buffer.at(0) + buffer_data.byteOffset));*/
}
void VertexBuffer::unBindVertex() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
unsigned int VertexBuffer::get_vbo_id() const {
    return this->id;
}