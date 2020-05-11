#pragma once
#include <glm.hpp>
#include <array>

class VertexBuffer {
private:
	unsigned int m_renderer_id;
public:
	VertexBuffer(const void* vertices, unsigned int size);
	~VertexBuffer();

	void bindVertex(const void* vertices, unsigned int size) const;
	void unBindVertex()const;
};
