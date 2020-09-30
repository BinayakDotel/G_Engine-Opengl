#pragma once
#include <glm.hpp>
#include <array>
#include <GLTFData.h>

class VertexBuffer {
private:
	unsigned int id;
	m_BufferView m_buffer;

public:
	VertexBuffer(m_BufferView m_buffer);
	~VertexBuffer();

	void bindVertex() const;
	void unBindVertex() const;

	unsigned int get_vbo_id() const;
};
