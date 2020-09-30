#pragma once

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

class VertexArray {
private:
	unsigned int m_renderer_id;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bindVertexArray() const;
	void unbindVertexArray() const;
};
